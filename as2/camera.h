#ifndef CAMERA
#define CAMERA
#include <string>
#include "vec3.h"
#include "ray.h"
#include "matrix3x3.h"


using namespace std;

class camera {
public:

  camera(vec3 eye = vec3(0,0,0), vec3 ll = vec3(0,0,0), vec3 lr = vec3(0,0,0), vec3 ul = vec3(0,0,0), vec3 ur = vec3(0,0,0));

  // u v range(0,1) as ratio
  ray generate_ray(double u, double v) const;

  unsigned int screen_w, screen_h;

private:

  vec3 eye, ll, lr, ul, ur;
};
#endif
