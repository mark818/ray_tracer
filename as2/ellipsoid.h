#ifndef ELLIPSOID
#define ELLIPSOID
#include "scene.h"
#include "vec4.h"
#include "matrix4x4.h"

class ellipsoid : public primitive {
public:

  ellipsoid(vec3& center, double r, vec3 ka, vec3 kd, vec4 ks, vec3 kr, matrix4x4 inv_m)
    : primitive(ka, kd, ks, kr), center(center), r(r), r2(r*r), inv_m(inv_m) {}

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
  matrix4x4 inv_m; // inverse matrix of the applied transformation matrix

};

#endif