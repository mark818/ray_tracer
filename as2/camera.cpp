#include "camera.h"

camera::camera(vec3 eye, vec3 ll, vec3 lr, vec3 ul, vec3 ur) 
  :eye(eye), ll(ll), lr(lr), ul(ul), ur(ur) {
    double ar = (lr-ll).norm()/(ul-ll).norm();
    screen_w = (ar > 1)? 800*ar:800;
    screen_h = (ar > 1)? 800:800*ar;
  }
  // Computes pos, screenXDir, screenYDir from target, r, phi, theta.
  void compute_position();

ray camera::generate_ray(double u, double v) const {
  vec3 point = u*(v*ll + (1-v)*ul) + (1-u)*(v*lr + (1-v)*ur);
  return ray(eye, point - eye);
}



