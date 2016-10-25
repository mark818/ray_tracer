#include "obj_parser.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;

vector<primitive*> obj_parser::parse() {
  ifstream f(filename);
  if (f.fail()) {
    cerr << "File not found.\n";
    return vector<primitive*>();
  }

  vector<vec3> vertices, normals;
  vertices.reserve(1000);
  normals.reserve(1000);
  vector<primitive*> primitives;
  primitives.reserve(1000);

  int vt_length = 0;

  char buf[100];
  while (f.getline(buf, 100)) {
    if (buf[0] == 0) {
      continue;
    }
    array<char *, 4> arr = string_split_4(buf);
    if (strcmp(arr[0], "v")) {
      double x = atof(arr[1]);
      double y = atof(arr[2]);
      double z = atof(arr[3]);
      vertices.emplace_back(x, y, z);
    } else if (strcmp(arr[0], "vn")) {
      double x = atof(arr[1]);
      double y = atof(arr[2]);
      double z = atof(arr[3]);
      normals.emplace_back(x, y, z);
    } else if (strcmp(arr[0], "vt")) {
      // texture not implemented
    } else if (strcmp(arr[0], "f")) {
      unsigned int vert[3], norm[3];
      if (!parse_face(arr, vert, norm, vertices.size(), normals.size())) {
        return vector<primitive*>();
      }
      const vec3 empty;
      const vec4 empty4;
      primitives.push_back(new triangle(vertices[vert[0]], vertices[vert[1]], vertices[vert[2]],
      normals[norm[0]], normals[norm[1]], normals[norm[2]], empty, empty, empty4, empty));
    }
  }
  return primitives;
}

array<char *, 4> obj_parser::string_split_4(char buf[], char delim) {
  array<char *, 4> arr;
  auto iter = arr.begin();
  arr[0] = buf;
  iter++;
  bool record = false;
  for (int i = 0; i < strlen(buf); i++) {
    if (buf[i] == delim || !record) {
      record = true;
    } else {
      if (record) {
        *iter = buf + i;
        record = false;
      }
    }
  }
  return arr;
}

bool obj_parser::parse_face(std::array<char*, 4>& line, unsigned int vert[], unsigned int norm[], size_t vert_len, size_t norm_len) {
  static int length = 0;
  unsigned int vertex, texture, normal;
  for (int i = 1; i < 3; i++) {
    // first use, determine face data format  1 = v/t   2 = v//n  3 = v/t/n
    if (length == 0) {
      char *cur = line[i];
      for (int i = 0; i < strlen(cur); i++) {
        if (cur[i] == '/') {
          if (cur[i + 1] == '/') {
            length = 2;
            break;
          } else if (length == 1) {
            length = 3;
            break;
          } else {
            length = 1;
          }
        }
      }
    }
    if (length == 2) {
      sscanf(line[1], "%ud%ud", &vertex, &normal);
    } else {
      sscanf(line[1], "%ud%ud%ud", &vertex, &texture, &normal); // texture not implemented
    }

    if (vertex >= vert_len || normal >= norm_len) {
      cerr << "Index out of bound.\n";
      return false;
    }
    vert[i - 1] = vertex;
    norm[i - 1] = normal;
  }
  return true;
}

