#include "light.h"
#include "float.h"
#include "cmath"


rgb directional_light::get_ray(vec3& p, vec3* dir_to_light, double* max_t) const {
  *dir_to_light = this->dir_to_light;
  *max_t = DBL_MAX;
  return radiance;
}

rgb point_light::get_ray(vec3& p, vec3* dir_to_light, double* max_t) const {
  *dir_to_light = this->pos - p;
  if (falloff == 0) {
  	*max_t = dir_to_light->norm();
  	return radiance;
  } else if (falloff == 1) {
  	*max_t = dir_to_light->norm();
  	return (radiance/ (*max_t));
  } else {
  	double r2 = dir_to_light->norm2();
  	*max_t = sqrt(r2);
  	return (radiance/r2);
  }
}
