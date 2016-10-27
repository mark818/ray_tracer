#ifndef CAMERA
#define CAMERA
#include <string>
#include "ray.h"
#include "matrix4x4.h"

using namespace std;

class camera {
public:

  camera(const vec3 & eye = vec3 (0,0,0), const vec3 & ll = vec3 (0,0,0), const vec3 & lr = vec3 (0,0,0), 
                                                                 const vec3 & ul = vec3 (0,0,0), const vec3 & ur = vec3 (0,0,0));
  
  void set_dof(const vec3 &target, double width, double height);
  bool has_dof() const { return dof; }

  void rotate_down(double d);
  void rotate_right(double d);

  // u v range(0,1) as ratio
  ray generate_ray(double u, double v) const;

  unsigned int screen_w, screen_h;
  double aperture_w, aperture_h;

private:
  
  vec3 eye, ll, lr, ul, ur, target;
  matrix4x4 target_to_origin, origin_to_target;
  vec3 orignal_pos;
  bool dof = false;
};
#endif
