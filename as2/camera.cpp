#include "camera.h"

camera::camera(vec3 eye, vec3 ll, vec3 lr, vec3 ul, vec3 ur) 
  :eye(eye), ll(ll), lr(lr), ul(ul), ur(ur) {
    double ar = (lr-ll).norm()/(ul-ll).norm();
    screen_w = static_cast<unsigned int>(ar > 1 ? 800 * ar : 800);
    screen_h = static_cast<unsigned int>((ar > 1)? 800:800*ar);
  }

ray camera::generate_ray(double u, double v) const {
  // vec3 point = ll + u * (lr - ll) + v * (ul - ll);
  vec3 point = (1-u)*(v*ll + (1-v)*ul) + u*(v*lr + (1-v)*ur);
  return ray(eye, (point - eye).unit());
}



