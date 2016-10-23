#ifndef CAMERA
#define CAMERA
#include "vec3.h"
#include "ray.h"
#include "matrix3x3.h"
#include "string"

using namespace std;

class camera {
public:


  camera(vec3 eye = vec3{0,0,0}, vec3 ll = vec3{0,0,0}, vec3 lr = vec3{0,0,0}, vec3 ul = vec3{0,0,0}, vec3 ur = vec3{0,0,0});

  // u v range(0,1) as ratio
  ray generate_ray(double u, double v) const;

 private:

  vec3 eye, ll, lr, ul, ur;

  size_t screen_w, screen_h;

};
#endif
