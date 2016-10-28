#ifndef TRIANGLE
#define TRIANGLE
#include "vec4.h"
#include "aabb.h"
#include "scene.h"
#include "intersection.h"


class triangle : public primitive {
public:

  triangle(const vec3 &A, const vec3 &B, const vec3 &C,
    const vec3 &ka, const vec3 &kd, vec4 &ks, const vec3 &kr)
    : primitive(ka, kd, ks, kr), v1(A), v2(B), v3(C), v1v2(v2 - v1), v1v3(v3 - v1), box(v1) {
    normal = n1 = n2 = n3 = cross(v1v2, v1v3).unit();
    box.expand(v2);
    box.expand(v3);
  }

  triangle(const vec3 &A, const vec3 &B, const vec3 &C,
    const vec3 &n1, const vec3 &n2, const vec3 &n3,
    const vec3 &ka, const vec3 &kd, const vec4 &ks, const vec3 &kr)
    : primitive(ka, kd, ks, kr), v1(A), v2(B), v3(C), n1(n1), n2(n2), n3(n3), v1v2(v2 - v1), v1v3(v3 - v1) {
    normal = cross(v1v2, v1v3).unit();
  }

  aabb get_aabb() const override {
    return box;
  }

  bool intersect(const ray& r) const override;
  bool intersect(const ray& r, intersection* i) const override;

private:
  void get_barycentric_coordinate(const vec3 &p, double &u, double &v, double &w) const;

  vec3 v1, v2, v3;
  vec3 v1v2, v1v3;
  vec3 n1, n2, n3;
  vec3 normal;
  aabb box;
};
#endif