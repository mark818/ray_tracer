#include "ellipsoid.h"
using namespace std;

aabb ellipsoid::get_aabb() const {
  return aabb(centroid - vec3(long_sa, long_sa, long_sa), centroid + vec3(long_sa, long_sa, long_sa));
}

bool ellipsoid::intersect(const ray &r) const {
  double t1, t2, max;
  vec3 inv_o, inv_d;
  vec4 o_vec4 = inv_m * vec4(r.o.x, r.o.y, r.o.z, 1);
  inv_o = trim_to_vec3(o_vec4/o_vec4.w);
  if (r.max<DBL_MAX) {
    vec3 end = r.o + r.max * r.d;
    vec4 end_vec4 = inv_m * vec4(end.x, end.y, end.z, 1);
    vec3 end_vec3 = trim_to_vec3(end_vec4/end_vec4.w);
    inv_d = (end_vec3 - inv_o).unit();
    max = (end_vec3 - inv_o).x/inv_d.x;
  } else {
    vec3 end = r.o + r.d;
    vec4 end_vec4 = inv_m * vec4(end.x, end.y, end.z, 1);
    vec3 end_vec3 = trim_to_vec3(end_vec4 / end_vec4.w);
    inv_d = (end_vec3 - inv_o).unit();
    max = r.max;
  }
  ray inv_r = ray(inv_o, inv_d, max, r.depth);
  if (test(inv_r, t1, t2)) {
    if (t2 > 0) {
      if (t1 > 0) {
        if (t1 <= inv_r.max) {
          return true;
        } else {
          return false;
        }
      }
      if (t2 <= inv_r.max) {
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
  double t1, t2, max;
  vec3 inv_o, inv_d;
  vec4 o_vec4 = inv_m * vec4(r.o.x, r.o.y, r.o.z, 1);
  inv_o = trim_to_vec3(o_vec4/o_vec4.w);
  if (r.max<DBL_MAX) {
    vec3 end = r.o + r.max * r.d;
    vec4 end_vec4 = inv_m * vec4(end.x, end.y, end.z, 1);
    vec3 end_vec3 = trim_to_vec3(end_vec4/end_vec4.w);
    inv_d = (end_vec3 - inv_o).unit();
    max = (end_vec3 - inv_o).norm();
  } else {
    vec3 end = r.o + r.d;
    vec4 end_vec4 = inv_m * vec4(end.x, end.y, end.z, 1);
    vec3 end_vec3 = trim_to_vec3(end_vec4 / end_vec4.w);
    inv_d = (end_vec3 - inv_o).unit();
    max = r.max;
  }
  ray inv_r = ray(inv_o, inv_d, max, r.depth);
  if (test(inv_r, t1, t2)) {
    if (t2 > 0) {
      if (t1 > 0) {
        if (t1 <= inv_r.max) {
          vec3 poi = inv_r.o + t1 * inv_r.d;
          vec4 t_poi4 = m * vec4(poi.x, poi.y, poi.z, 1);
          vec3 t_poi3 = trim_to_vec3(t_poi4/t_poi4.w);
          double true_t1;
          for (int i = 0; i < 3; i++) {
            if (r.d[i] != 0) {
              true_t1 = (t_poi3 - r.o)[i] / r.d[i];
              break;
            }
          }
          i->t = true_t1;
          i->p = this;
          i->n = normal(t_poi3);
          return true;
        } else {
          return false;
        }
      } else {
        if (t2 <= inv_r.max) {
          vec3 poi = inv_r.o + t2 * inv_r.d;
          vec4 t_poi4 = m * vec4(poi.x, poi.y, poi.z, 1);
          vec3 t_poi3 = trim_to_vec3(t_poi4/t_poi4.w);
          double true_t2;
          for (int i = 0; i < 3; i++) {
            if (r.d[i] != 0) {
              true_t2 = (t_poi3 - r.o)[i] / r.d[i];
              break;
            }
          }
          i->t = true_t2;
          i->p = this;
          i->n = normal(t_poi3);
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
  vec3 ori_n = p - center;
  // transformed normal is the M^-T * original normal
  vec4 new_n4 = inv_m * vec4(ori_n.x, ori_n.y, ori_n.z, 1);
  vec3 new_n3 = trim_to_vec3(new_n4/new_n4.w).unit();
  return new_n3;
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
