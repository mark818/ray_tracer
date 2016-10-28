#ifndef ELLIPSOID
#define ELLIPSOID
#include "scene.h"
#include "vec4.h"
#include "matrix4x4.h"
#include <algorithm>


class ellipsoid : public primitive {
public:

  ellipsoid(vec3& center, double r, vec3 ka, vec3 kd, vec4 ks, vec3 kr, matrix4x4 m, matrix4x4 inv_m)
    : primitive(ka, kd, ks, kr), center(center), r(r), r2(r*r), m(m), inv_m(inv_m)  {
      long_sa = r * std::max(std::max(m(0, 0), m(1, 1)), m(2, 2));
      vec4 center4 = m * vec4(center.x, center.y, center.z, 1);
      centroid = trim_to_vec3(center4 / center4.w);
      box = aabb(centroid - vec3(long_sa, long_sa, long_sa), centroid + vec3(long_sa, long_sa, long_sa));
    }

  aabb get_aabb() const override;

  bool intersect(const ray& r) const override;

  bool intersect(const ray& r, intersection* i) const override;

  vec3 normal(vec3 p) const;

private:

  bool test(const ray& r, double& t1, double& t2) const;

  vec3 center; // origin of the sphere
  vec3 centroid; // transformed center
  double r;   // radius
  double r2;  // radius squared
  matrix4x4 m;  // applied transformation matrix
  matrix4x4 inv_m; // inverse matrix of the applied transformation matrix
  double long_sa;
  aabb box;
};

#endif