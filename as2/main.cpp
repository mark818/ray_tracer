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
using namespace std;

const double PI = 3.141592653589793;

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

int main(int argc, char *argv[]) {
  std::vector<primitive *> primitives;
  std::vector<light *> lights;
  rgb ambient_l{0, 0, 0};
  vec3 ka{0, 0, 0};
  vec3 kd{0, 0, 0};
  vec4 ks{0, 0, 0, 0};
  vec3 kr{0, 0, 0};

  matrix4x4 cur_matrix = matrix4x4::identity();
  camera my_camera;

  string line, word, filename;
  stringstream ss;
  bool fail;
  while (getline(cin, line)) {
    ss << line;
    ss >> word;
    if (word == "cam") {
      array<double, 15> arr = readline<15>(ss, &fail);
      if (!fail) {
        vec3 eye{arr[0], arr[1], arr[2]};
        vec3 ll{arr[3], arr[4], arr[5]};
        vec3 lr{arr[6], arr[7], arr[8]};
        vec3 ul{arr[9], arr[10], arr[11]};
        vec3 ur{arr[12], arr[13], arr[14]};
        my_camera = camera(eye, ll, lr, ul, ur);
      }
    } else if (word == "sph") {
      array<double, 4> arr = readline<4>(ss, &fail);
      if (!fail) {      
        vec3 center{arr[0], arr[1], arr[2]};
        vec3 ellipsoid_cof{(double)1, (double)1, (double)1};
        double r = arr[3];
        // do transformation
        primitives.push_back(new ellipsoid(center, ellipsoid_cof, r, ka, kd, ks, kr));
      }
    } else if (word == "tri") {
      array<double, 9> arr = readline<9>(ss, &fail);
      if (!fail) {
        vec4 v1{arr[0], arr[1], arr[2], 0};
        vec4 v2{arr[3], arr[4], arr[5], 0};
        vec4 v3{arr[6], arr[7], arr[8], 0};
        vec3 A = trim_to_vec3(cur_matrix*v1);
        vec3 B = trim_to_vec3(cur_matrix*v2);
        vec3 C = trim_to_vec3(cur_matrix*v3);
        primitives.push_back(new triangle(A, B, C, ka, kd, ks, kr));
      }
    } else if (word == "obj") {
      if (!ss.eof()) {
        ss >> filename;
        if (!ss.eof()) {
          cerr << "Extra paramters.\n";
        }
      } else {
        cerr << "File name missing.\n";
      }
    } else if (word == "ltp") {
      int falloff;
      array<double, 6> arr = readline<6>(ss, &falloff, &fail);
      if (!fail) {
        vec3 light_pos = vec3{arr[0], arr[1], arr[2]};
        vec3 rad = vec3{arr[3], arr[4], arr[5]};
        lights.push_back(new point_light(rad, light_pos, falloff));
      }
    } else if (word == "ltd") {
      array<double, 6> arr = readline<6>(ss, &fail);
      if (!fail) {
        vec3 light_dir = vec3{arr[0], arr[1], arr[2]};
        vec3 rad = vec3{arr[3], arr[4], arr[5]};
        lights.push_back(new directional_light(rad, light_dir));
      }
    } else if (word == "lta") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        ambient_l = rgb{arr[0], arr[1], arr[2]};
      }
    } else if (word == "mat") {
      array<double, 13> arr = readline<13>(ss, &fail);
      if (!fail) {
        ka = vec3{arr[0], arr[1], arr[2]};
        kd = vec3{arr[3], arr[4], arr[5]};
        ks = vec4{arr[6], arr[7], arr[8], arr[9]};
        kr = vec3{arr[10], arr[11], arr[12]};
      }
    } else if (word == "xft") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        matrix4x4 m = matrix4x4::identity();
        m.column(3) = vec4{arr[0], arr[1], arr[2], (double)1};
        cur_matrix = m * cur_matrix;
      }
    } else if (word == "xfr") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        double theta = sqrt(sqr(arr[0]) + sqr(arr[1]) + sqr(arr[2])) / 180 * PI;
        double sin_theta = sin(theta);
        double cos_theta = cos(theta);
        double data[] = {0, -arr[2], arr[1], 
                         arr[2], 0, -arr[0],
                         -arr[1], arr[0], 0};
        matrix3x3 Rx = matrix3x3(data);
        double r_data[] = {arr[0]*arr[0], arr[0]*arr[1], arr[0]*arr[2],
                           arr[1]*arr[0], arr[1]*arr[1], arr[2]*arr[2],
                           arr[2]*arr[0], arr[2]*arr[1], arr[2]*arr[2]};
        matrix3x3 rr = matrix3x3(r_data);
        matrix3x3 m = rr + sin_theta * Rx - cos_theta * Rx * Rx;
        matrix4x4 m4 = extend_to_matrix4x4(m);
        cur_matrix = m4 * cur_matrix;
      }
    } else if (word == "xfs") {
      array<double, 3> arr = readline<3>(ss, &fail);
      if (!fail) {
        double data[] = {arr[0], 0, 0, 0,
                         0, arr[1], 0, 0,
                         0, 0, arr[2], 0,
                         0, 0, 0, 1 };
        matrix4x4 m(data);       
        cur_matrix = m * cur_matrix;
      }
    } else if (word == "xfz") {
      cur_matrix = matrix4x4::identity();
    } else {
      cerr << "Unsupported feature.\n"; 
    }
    ss.str(string());
  }
  scene my_scene(primitives, lights);
}