#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctype.h>
#include "ray_tracer.h"
using namespace std;

vec3 ka, kd, ks;
double sp, spu, spv;
bool isSp = false;
vector<light> lights;

double is_valid_double(char *str) {
  static stringstream ss;
  ss.clear();
  ss << str;
  double res;
  ss >> res;
  if (!ss.fail())
    return res;
  return -FLT_MAX;
}

void set_ka(double r, double g, double b) {
  ka = { r, g, b };
}

void set_kd(double r, double g, double b) {
  kd = { r, g, b };
}

void set_ks(double r, double g, double b) {
  ks = { r, g, b };
}

void set_spu(double val) {
  spu = val;
}

void set_spv(double val) {
  spv = val;
}

void set_sp(double val) {
  sp = val;
}

void set_pl(double x, double y, double z, double r, double g, double b) {
  //lights.push_back({ true, vec3{ x, y, z }, r, g, b });
}

void set_dl(double x, double y, double z, double r, double g, double b) {
  //lights.push_back({ false, vec3{ x, y, z }, r, g, b });
}


inline bool is_within(double val, double max, double min = 0) {
  return val >= min && val <= max;
}

inline void quit_with_error() {
  cerr << "Invalid arguments.\n";
  exit(-1);
}

template <int N>
array<double, N>&& readline(stringstream &ss) {
  return move(array<double, N>());
}

int main(int argc, char *argv[]) {
  string line, word, filename;
  stringstream ss;
  while (getline(cin, line)) {
    ss << line;
    ss >> word;
    if (word == "cam") {
      array<double, 15> &&arr = readline<15>(ss);

    } else if (word == "sph") {
      array<double, 4> &&arr = readline<4>(ss);
    } else if (word == "tri") {
      array<double, 9> &&arr = readline<9>(ss);
    } else if (word == "obj") {
      if (!ss.eof()) {
        ss >> filename;
      } else {
        cerr << "File name missing.\n";
      }
    } else if (word == "ltp") {
      array<double, 6> &&arr = readline<6>(ss);
      int falloff = 0;
      if (!ss.eof()) {
        ss >> falloff;
        if (falloff < 0 || falloff > 4) {
          cerr << "Invalid falloff value.\n";
          falloff = 0;
        }
      }
    } else if (word == "ltd") {
      array<double, 6> &&arr = readline<6>(ss);
    } else if (word == "lta") {
      array<double, 3> &&arr = readline<3>(ss);
    } else if (word == "mat") {
      array<double, 13> &&arr = readline<13>(ss);
    } else if (word == "xft") {
      array<double, 3> &&arr = readline<3>(ss);
    } else if (word == "xfr") {
      array<double, 3> &&arr = readline<3>(ss);
    } else if (word == "xfs") {
      array<double, 3> &&arr = readline<3>(ss);
    } else if (word == "xfz") {

    } else {
      cerr << "Unsupported feature.\n"; 
    }
    ss.str(string());
  }
}