#ifndef CAMERA
#define CAMERA
#include <string>
#include <vector>
#include "ray.h"
#include "matrix4x4.h"

using namespace std;

class camera {
public:

  camera(const vec3 & eye = vec3 (0,0,0), const vec3 & ll = vec3 (0,0,0), const vec3 & lr = vec3 (0,0,0), 
                                                                 const vec3 & ul = vec3 (0,0,0), const vec3 & ur = vec3 (0,0,0));
  
  void set_dof(double focal_d, double aperture);
  bool has_dof() const { return dof; }

  // u v range(0,1) as ratio

  ray generate_ray(double u, double v) const;
  std::vector<ray> generate_ray_bundle(double u, double v) const;

  unsigned int screen_w, screen_h;
  double ar; //aspect ratio


private:
  vec3 get_point_on_screen(double u, double v) const;
  vec3 eye, ll, lr, ul, ur;
  double focal_d, aperture;
  bool dof = false;
};
#endif
