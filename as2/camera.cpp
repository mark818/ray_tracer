#include "camera.h"
#include <cmath>

camera::camera(const vec3 &eye, const vec3 &ll, const vec3 &lr, const vec3 &ul, const vec3 &ur) 
  :eye(eye), ll(ll), lr(lr), ul(ul), ur(ur) {
    ar = (lr-ll).norm()/(ul-ll).norm();
    screen_w = static_cast<unsigned int>(ar > 1 ? 1000 * ar : 1000);
    screen_h = static_cast<unsigned int>((ar > 1)? 1000:1000*ar);
  }

void camera::set_dof(const vec3 &target, double width, double height) {
  aperture_w = width;
  aperture_h = height;
  this->target = target;
  double t2o[] = { 1, 0, 0, -target.x,
                            0, 1, 0, -target.y,
                            0, 0, 1, -target.z, 
                            0, 0, 0, 1};
  target_to_origin = matrix4x4(t2o);
  double o2t[] = { 1, 0, 0, target.x,
                           0, 1, 0, target.y,
                           0, 0, 1, target.z,
                           0, 0, 0, 1 };
  origin_to_target = matrix4x4(o2t);
  orignal_pos = eye;
  dof = true;
}

void camera::rotate_down(double rad) {
  double data[] = { 1, 0, 0, 0,
                             0, cos(rad), -sin(rad), 0,
                             0, sin(rad), cos(rad), 0,
                             0, 0, 0, 1 };
  matrix4x4 rotate_by_x(data);
  eye = trim_to_vec3(target_to_origin * rotate_by_x * origin_to_target * expand_to_vec4(orignal_pos));
}

void camera::rotate_right(double rad) {
  double data[] = { cos(rad), 0, sin(rad), 0,
                             0, 1, 0, 0,
                             -sin(rad), 0, cos(rad), 0, 0,
                             0, 0, 0, 1};
  matrix4x4 rotate_by_x(data);
  eye = trim_to_vec3(target_to_origin * rotate_by_x * origin_to_target * expand_to_vec4(orignal_pos));
}

ray camera::generate_ray(double u, double v) const {
  // const vec3 &point = ll + u * (lr - ll) + v * (ul - ll);
  const vec3 &point = (1-u)*((1-v)*ll + v*ul) + u*((1-v)*lr + v*ur);
  return ray(eye, (point - eye).unit());
}



