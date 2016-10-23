#ifndef AABB
#define AABB

#include <float.h>
#include <vector>
#include "vec3.h"
#include "ray.h"

class primitive;

struct aabb {
  vec3 max;
  vec3 min;
  aabb* left;
  aabb* right; 
  std::vector<primitive*> primitives;

  aabb()
    :max(vec3{-DBL_MAX, -DBL_MAX, -DBL_MAX}), min(vec3{ DBL_MAX,  DBL_MAX,  DBL_MAX}), left(0), right(0) {}

  aabb(const vec3 &min, const vec3 &max, aabb* left = 0, aabb* right = 0) 
    :max(max), min(min), left(left), right(right) {}

  aabb(const vec3 &p)
    :max(p), min(p), left(0), right(0) {}

  bool is_leaf() {return ((left == 0) && (right == 0));}

  vec3 centroid() const {
    return (min + max) / 2;
  }

  void expand(const aabb& box);

  void expand(const vec3& p);

  bool intersect(const ray& r, double& t0, double& t1) const;

};

#endif