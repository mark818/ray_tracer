#include "light.h"
#include "float.h"


rgb directional_light::get_ray(vec3& p, vec3* dir_to_light, double* max_t) const {
  *dir_to_light = this->dir_to_light;
  *max_t = DBL_MAX;
  return radiance;
}

rgb point_light::get_ray(vec3& p, vec3* dir_to_light, double* max_t) const {
  *dir_to_light = this->pos - p;
  *max_t = dir_to_light->norm();
  return radiance;
}
