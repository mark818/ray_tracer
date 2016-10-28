#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctype.h>
#include "ray_tracer.h"
#include "vec4.h"
#include "matrix3x3.h"
#include "matrix4x4.h"
#include "triangle.h"
#include "ellipsoid.h"
#include "obj_parser.h"
using namespace std;

const double PI = 3.141592653589793238462643383279502884197169399375106;

template <int N>
array<double, N> readline(stringstream &ss, bool *fail) {
  array<double, N> arr;
  for (int i = 0; i < N; i++) {
    if (ss.eof()) {
      cerr << "Not enough paramters.\n";
    }

    double val;
    ss >> val;
    arr[i] = val;

    if (ss.fail()) {
      cerr << "Invalid value type.\n";
      *fail = true;
      return arr;
    }
  }
  *fail = false;
  if (!ss.eof()) {
    cerr << "Extra paramters.\n";
  }
  return arr;
}

template <int N>
array<double, N> readline(stringstream &ss, int *falloff, bool *fail) {
  array<double, N> arr;
  for (int i = 0; i < N; i++) {
    if (ss.eof()) {
      cerr << "Not enough paramters.\n";
    }

    double val;
    ss >> val;
    arr[i] = val;

    if (ss.fail()) {
      cerr << "Invalid value type.\n";
      *fail = true;
      return arr;
    }
  }
  *fail = false;
  *falloff = 0;
  if (!ss.eof()) {
    ss >> *falloff;
    if (*falloff < 0 || *falloff > 2) {
      cerr << "Invalid falloff value.\n";
      *falloff = 0;
    }
  }
  if (!ss.eof()) {
    cerr << "Extra paramters.\n";
  }
  return arr;
}

int __cdecl main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::vector<primitive *> primitives;
  std::vector<light *> lights;
  rgb ambient_l(0, 0, 0);
  vec3 ka(0, 0, 0);
  vec3 kd(0, 0, 0);
  vec4 ks(0, 0, 0, 0);
  vec3 kr(0, 0, 0);

  matrix4x4 cur_matrix = matrix4x4::identity();
  camera my_camera;

  int depth = 0;
  int num_threads = 1;
  int msaa = 1;
  string line, word, scene_name, filename = "img.png";
  stringstream ss;
  bool fail;
  while (getline(cin, line)) {
    if (line.empty()) {
      continue;
    }
    ss.str(move(line));
    ss >> word;
    if (word == "cam") {
      array<double, 15> arr = readline<15>(ss, &fail);
      if (!fail) {
        vec3 eye(arr[0], arr[1], arr[2]);
        vec3 ll(arr[3], arr[4], arr[5]);
        vec3 lr(arr[6], arr[7], arr[8]);
        vec3 ul(arr[9], arr[10], arr[11]);
        vec3 ur(arr[12], arr[13], arr[14]);
        my_camera = camera(eye, ll, lr, ul, ur);
      }
    } else if (word == "sph") {
      array<double, 4> arr = readline<4>(ss, &fail);
      if (!fail) {      
        vec3 center(arr[0], arr[1], arr[2]);
        double r = arr[3];
        // do transformation
        matrix4x4 inv_m = cur_matrix.inv();
        primitives.push_back(new ellipsoid(center, r, ka, kd, ks, kr, cur_matrix, inv_m));
      }
    } else if (word == "tri") {
      array<double, 9> arr = readline<9>(ss, &fail);
      if (!fail) {
        vec4 v1(arr[0], arr[1], arr[2], 1);
        vec4 v2(arr[3], arr[4], arr[5], 1);
        vec4 v3(arr[6], arr[7], arr[8], 1);
        vec3 A = trim_to_vec3(cur_matrix*v1);
        vec3 B = trim_to_vec3(cur_matrix*v2);
        vec3 C = trim_to_vec3(cur_matrix*v3);
        primitives.push_back(new triangle(A, B, C, ka, kd, ks, kr));
      }
    } else if (word == "obj") {
      if (!ss.eof()) {
        ss >> scene_name;
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        } 
        obj_parser parser(scene_name, ka, kd, ks, kr);
        vector<primitive *>from_file = parser.parse();
        primitives.insert(primitives.end(), from_file.begin(), from_file.end());
      } else {
        cerr << "File name missing.\n";
      }
    } else if (word == "ltp") {
      int falloff;
      array<double, 6> arr = readline<6>(ss, &falloff, &fail);
      if (!fail) {
        vec3 light_pos = vec3(arr[0], arr[1], arr[2]);
        vec3 rad = vec3(arr[3], arr[4], arr[5]);
        lights.push_back(new point_light(rad, light_pos, falloff));
      }
    } else if (word == "ltd") {
      array<double, 6> arr = readline<6>(ss, &fail);
      if (!fail) {
        vec3 light_dir = vec3(arr[0], arr[1], arr[2]);
        vec3 rad = vec3(arr[3], arr[4], arr[5]);
        lights.push_back(new directional_light(rad, light_dir));
      }
    } else if (word == "lta") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        ambient_l = rgb(arr[0], arr[1], arr[2]);
      }
    } else if (word == "mat") {
      array<double, 13> arr = readline<13>(ss, &fail);
      if (!fail) {
        ka = vec3(arr[0], arr[1], arr[2]);
        kd = vec3(arr[3], arr[4], arr[5]);
        ks = vec4(arr[6], arr[7], arr[8], arr[9]);
        kr = vec3(arr[10], arr[11], arr[12]);
      }
    } else if (word == "xft") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        matrix4x4 m = matrix4x4::identity();
        m.column(3) = vec4(arr[0], arr[1], arr[2], (double)1);
        cur_matrix = m * cur_matrix;
      }
    } else if (word == "xfr") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        vec3 r_n = vec3(arr[0], arr[1], arr[2]).unit();
        double theta = sqrt(sqr(arr[0]) + sqr(arr[1]) + sqr(arr[2])) / 180 * PI;
        double sin_theta = sin(theta);
        double cos_theta = cos(theta);
        double data[] = { 0, -r_n.z, r_n.y,
                         r_n.z, 0, -r_n.x,
                         -r_n.y, r_n.x, 0 };
        matrix3x3 Rx = matrix3x3(data);
        double r_data[] = { r_n.x * r_n.x, r_n.x * r_n.y, r_n.x * r_n.z,
                           r_n.y * r_n.x, r_n.y * r_n.y, r_n.y * r_n.z,
                           r_n.z * r_n.x, r_n.z * r_n.y, r_n.z * r_n.z };
        matrix3x3 rr = matrix3x3(r_data);
        matrix3x3 m = rr + sin_theta * Rx - cos_theta * Rx * Rx;
        matrix4x4 m4 = extend_to_matrix4x4(m);
        cur_matrix = m4 * cur_matrix;
      }
    } else if (word == "xfs") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        double data[] = { arr[0], 0, 0, 0,
                         0, arr[1], 0, 0,
                         0, 0, arr[2], 0,
                         0, 0, 0, 1 };
        matrix4x4 m(data);       
        cur_matrix = m * cur_matrix;
      }
    } else if (word == "xfz") {
      cur_matrix = matrix4x4::identity();
    } else if (word == "save") {
      if (!ss.eof()) {
        ss >> filename;
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        }
      }
    } else if (word == "size") {
      if (!ss.eof()) {
        double size;
        ss >> size;
        if (size < 700) {
          cerr << "Size too small to render.\n"; 
        } else if (size > 3000) {
          cerr << "Size too large to render.\n"; 
        } else{
          double ar = my_camera.ar;
          my_camera.screen_w = static_cast<unsigned int>(ar > 1 ? size * ar : size);
          my_camera.screen_h = static_cast<unsigned int>((ar > 1)? size:size*ar);
        }
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        }
      }
    } else if (word == "d") {
      if (!ss.eof()) {
        ss >> depth;
        if (depth < 0) {
          depth = 0;
          cerr << "Unsupported feature.\n"; 
        }
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        }
      }
    } else if (word == "t") {
      if (!ss.eof()) {
        ss >> num_threads;
        if (num_threads <= 0) {
          num_threads = 1;
          cerr << "Unsupported feature.\n"; 
        }
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        }
      }
    } else if (word == "aa") {
      if (!ss.eof()) {
        ss >> msaa;
        if (msaa <= 0) {
          msaa = 1;
          cerr << "Unsupported feature.\n"; 
        }
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        }
      }
    } else if (word == "dof") { // target.x target.y target.z aperture.w aperture.h
      array<double, 5> arr = readline<5>(ss, &fail);
      if (!fail) {
        my_camera.set_dof(vec3(arr[0], arr[1], arr[2]), arr[3], arr[4]);
      }
    } else {
      cerr << "Invalid dof arguments.\n"; 
    }
    ss.clear();
  }
  if (!scene_name.empty()) {
   
  }
  scene my_scene(primitives, lights, ambient_l);
  ray_tracer my_ray_tracer(my_camera, my_scene, filename, num_threads, msaa, depth);
  my_ray_tracer.begin();
  return 0;
}