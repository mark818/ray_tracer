#ifndef CAMERA
#define CAMERA
#include "vec3.h"
#include "ray.h"
#include "matrix3x3.h"
#include "string"

using namespace std;

class camera {
public:

  camera(vec3 eye, vec3 ll, vec3 lr, vec3 ul, vec3 ur);

  // u v range(0,1) as ratio
  ray generate_ray(double u, double v) const;

 private:

  vec3 eye, ll, lr, ul, ur;
  // Computes pos, screenXDir, screenYDir from target, r, phi, theta.
  void compute_position();

  size_t screen_w, screen_h;

};
#endif
