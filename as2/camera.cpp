#include "camera.h"
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

camera::camera(const vec3 &eye, const vec3 &ll, const vec3 &lr, const vec3 &ul, const vec3 &ur)
  :eye(eye), ll(ll), lr(lr), ul(ul), ur(ur) {
  ar = (lr - ll).norm() / (ul - ll).norm();
  screen_w = static_cast<unsigned int>(ar > 1 ? 1000 * ar : 1000);
  screen_h = static_cast<unsigned int>((ar > 1) ? 1000 : 1000 * ar);
}

void camera::set_dof(double focal_d, double aperture) {
  this->focal_d = focal_d;
  this->aperture = aperture;
  srand(clock());
  dof = true;
}

vec3 camera::get_point_on_screen(double u, double v) const {
  return (1 - u)*((1 - v)*ll + v*ul) + u*((1 - v)*lr + v*ur);
}

ray camera::generate_ray(double u, double v) const {
  const vec3 point = get_point_on_screen(u, v);
  return ray(eye, (point - eye).unit());
}

vector<ray> camera::generate_ray_bundle(double u, double v) const {
  static double radius = aperture / 2;
  vector<ray> bundle;
  const vec3 point = get_point_on_screen(u, v);
  const vec3 focus = generate_ray(u, v).at_time(focal_d);
  for (int i = 0; i < 9; i++) {
    double hor = static_cast<double>(rand()) / RAND_MAX * aperture - radius;
    double ver = static_cast<double>(rand()) / RAND_MAX * aperture - radius;
    vec3 origin(point.x + hor, point.y + ver, point.z);
    bundle.emplace_back(origin, (focus - origin).unit());
  }
  return bundle;
}



