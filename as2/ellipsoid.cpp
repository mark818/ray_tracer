#include "ellipsoid.h"

bool ellipsoid::intersect(const ray &r) const {
  double t1, t2;
  if (test(r, t1, t2)) {
    if (t2 > 0) {
      if (t1 > 0) {
        if (t1 <= r.max) {
          return true;
        } else {
          return false;
        }
      }
      if (t2 <= r.max) {
        return true;
      }
      return false;
    }
    return false;
  } else {
    return false;
  }
}


bool ellipsoid::intersect(const ray& r, intersection* i) const {
  double t1, t2;
  if (test(r, t1, t2)) {
    if (t2 > 0) {
      if (t1 > 0) {
        if (t1 <= r.max) {
          i->t = t1;
          i->p = this;
          i->n = normal(r.o + t1*r.d);
          return true;
        } else {
          return false;
        }
      } else {
        if (t2 <= r.max) {
          i->t = t2;
          i->p = this;
          i->n = normal(r.o + t2*r.d);
          return true;
        } else {
          return false;
        }
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

vec3 ellipsoid::normal(vec3 p) const {
  vec3 direction;
  direction.x = cof_sqr.y*cof_sqr.z*(p.x-center.x);
  direction.y = cof_sqr.x*cof_sqr.z*(p.y-center.y);
  direction.z = cof_sqr.x*cof_sqr.y*(p.z-center.z);
  return direction.unit();
}

bool ellipsoid::test(const ray& r, double& t1, double& t2) const {
  double denominator = cof_sqr.x + cof_sqr.y + cof_sqr.z;
  double a = dot(r.d, r.d) / denominator;
  double b = 2*(r.o.x + r.o.y + r.o.z)/ denominator;
  double c = dot(r.o, r.o) / denominator - r2;
  double delta = b * b - 4 * a * c;
  if (delta >= 0) {
    t1 = (-b - sqrt(delta)) / 2 / a;
    t2 = (-b + sqrt(delta)) / 2 / a;
    return true;
  } else {
    return false;
  }
}
