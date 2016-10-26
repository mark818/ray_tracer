#ifndef ELLIPSOID
#define ELLIPSOID
#include "scene.h"
#include "vec4.h"

class ellipsoid : public primitive {
public:

  ellipsoid(vec3& center, vec3& ellipsoid_cof, double r, vec3 ka, vec3 kd, vec4 ks, vec3 kr)
    : primitive(ka, kd, ks, kr), center(center), r(r), r2(r*r) {}

  aabb get_aabb() const override {
    return aabb(center - vec3(r, r, r), center + vec3(r, r, r));
  }

  bool intersect(const ray& r) const override;

  bool intersect(const ray& r, intersection* i) const override;

  vec3 normal(vec3 p) const;

private:

  bool test(const ray& r, double& t1, double& t2) const;

  vec3 center; // origin of the sphere
  double r;   // radius
  double r2;  // radius squared

};

#endif