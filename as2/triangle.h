#ifndef TRIANGLE
#define TRIANGLE
#include "vec4.h"
#include "aabb.h"
#include "scene.h"
#include "intersection.h"


class triangle : public primitive {
public:

  triangle(vec3 A, vec3 B, vec3 C, vec3 ka, vec3 kd, vec4 ks, vec3 kr)
    : primitive(ka, kd, ks, kr), v1(A), v2(B), v3(C) { }

  aabb get_aabb() {
  	aabb box(v1);
  	box.expand(v2);
  	box.expand(v3);
	  return box;
  }

  bool intersect(const ray& r) const;


  bool intersect(const ray& r, intersection* i) const;

private:

  vec3 v1, v2, v3;

};
#endif