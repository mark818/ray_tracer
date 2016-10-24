#ifndef RAY
#define RAY
#include <math.h>
#include "vec3.h"
#include "float.h"

struct ray {
  size_t depth;  
  vec3 o, d; 
  mutable double min, max;
  vec3 inv_d; 
  int sign[3]; 

  ray(const vec3 &o, const vec3 &d, size_t depth = 0)
    : o(o), d(d), min(0.0), max(DBL_MAX), depth(depth) {
    inv_d = vec3{ 1 / d.x, 1 / d.y, 1 / d.z };
    sign[0] = (inv_d.x < 0);
    sign[1] = (inv_d.y < 0);
    sign[2] = (inv_d.z < 0);
  }

  /**
  * Constructor.
  * Create a ray instance with given origin and direction.
  * \param o origin of the ray
  * \param d direction of the ray
  * \param max_t max t value for the ray (if it's actually a segment)
  * \param depth depth of the ray
  */
  ray(const vec3& o, const vec3& d, double max_t, size_t depth = 0)
    : o(o), d(d), min(0.0), max(DBL_MAX), depth(depth) {
    inv_d = vec3{ 1 / d.x, 1 / d.y, 1 / d.z };
    sign[0] = (inv_d.x < 0);
    sign[1] = (inv_d.y < 0);
    sign[2] = (inv_d.z < 0);
  }

  inline vec3 at_time(double t) const { return o + t * d; }
};

#endif

