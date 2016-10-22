#ifndef AABB
#define AABB

#include "float.h"
#include "vec3.h"
#include "ray.h"

struct aabb {
  vec3 max;
  vec3 min;

  aabb(const vec3 &min, const vec3 &max) 
  : max(max), min(min) {}

  aabb(const vec3 &p)
  : max(p), min(p) {}

  vec3 centroid() const {
    return (min + max) / 2;
  }

  void expand(const aabb& box);

  void expand(const vec3& p);

  bool intersect(const ray& r, double& t0, double& t1) const;

};

#endif