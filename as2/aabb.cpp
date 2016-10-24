#include "aabb.h"
#include <algorithm>
#include <math.h>

void aabb::expand(const aabb& box) {
  min.x = std::min(min.x, box.min.x);
  min.y = std::min(min.y, box.min.y);
  min.z = std::min(min.z, box.min.z);
  max.x = std::max(max.x, box.max.x);
  max.y = std::max(max.y, box.max.y);
  max.z = std::max(max.z, box.max.z);
}

void aabb::expand(const vec3& p) {
  min.x = std::min(min.x, p.x);
  min.y = std::min(min.y, p.y);
  min.z = std::min(min.z, p.z);
  max.x = std::max(max.x, p.x);
  max.y = std::max(max.y, p.y);
  max.z = std::max(max.z, p.z);
}

bool aabb::intersect(const ray& r, double& t0, double& t1) const {

  double tmin, tmax, tymin, tymax, tzmin, tzmax;

  vec3 bounds[2];
  bounds[0] = min;
  bounds[1] = max;

  if (isinf(r.inv_d.x)) {
    tmin = -DBL_MAX;
    tmax = DBL_MAX;
  } else {
    tmin = (bounds[r.sign[0]].x - r.o.x) * r.inv_d.x;
    tmax = (bounds[1 - r.sign[0]].x - r.o.x) * r.inv_d.x;
  }
  if (isinf(r.inv_d.y)) {
    tymin = -DBL_MAX;
    tymax = DBL_MAX;
  } else {
    tymin = (bounds[r.sign[1]].y - r.o.y) * r.inv_d.y;
    tymax = (bounds[1 - r.sign[1]].y - r.o.y) * r.inv_d.y;
  }

  if ((tmin > tymax) || (tymin > tmax)) {
    return false;
  }
  if (tymin > tmin) {
    tmin = tymin;
    t0 = tmin;
  }
  if (tymax < tmax) {
    tmax = tymax;
    t1 = tmax;
  }
  if (isinf(r.inv_d.z)) {
    return true;
  }

  tzmin = (bounds[r.sign[2]].z - r.o.z) * r.inv_d.z;
  tzmax = (bounds[1-r.sign[2]].z - r.o.z) * r.inv_d.z;
  if ((tmin > tzmax || tzmin > tmax)) {
    return false;
  }
  if (tzmin > tmin) {
    tmin = tzmin;
    t0 = tmin;
  } 
  if (tzmax < tmax) {
    tmax = tzmax;
    t1 = tmax;
  }
  return ((tmin < t1) && (tmax > t0));
}
