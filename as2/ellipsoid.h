#ifndef ELLIPSOID
#define ELLIPSOID
#include "scene.h"
#include "vec3.h"

class ellipsoid : public primitive {
public:

  ellipsoid(vec3& center, vec3& ellipsoid_cof, double r)
    : center(center), ellipsoid_cof(ellipsoid_cof), r(r), r2(r*r), cof_sqr(modmul(ellipsoid_cof, ellipsoid_cof)) { }

  aabb get_aabb() {
    vec3 v = vec3{ellipsoid_cof.x*r, ellipsoid_cof.y*r, ellipsoid_cof.z*r};
    return aabb(center - v, center + v);
  }

  bool intersect(const ray& r) const;

  bool intersect(const ray& r, intersection* i) const;

  vec3 normal(vec3 p) const;

 private:

  bool test(const ray& r, double& t1, double& t2) const;

  vec3 center; ///< origin of the sphere
  vec3 ellipsoid_cof;
  double r;   ///< radius
  double r2;  ///< radius squared
  vec3 cof_sqr; /// for calculation of normal

};

#endif