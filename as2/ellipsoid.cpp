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
  return (p-center).unit();
}

bool ellipsoid::test(const ray& r, double& t1, double& t2) const {
  double a = dot(r.d, r.d);
  double b = 2.0 * dot(r.o - center, r.d);
  double c = dot(r.o - center, r.o - center) - r2;
  double delta = b * b - 4 * a * c;
  if (delta >= 0) {
    t1 = (-b - sqrt(delta)) / 2 / a;
    t2 = (-b + sqrt(delta)) / 2 / a;
    return true;
  } else {
    return false;
  }
}
