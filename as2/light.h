#ifndef LIGHT
#define LIGHT
#include "vec3.h"
#include "scene.h"


class directional_light:public light{
public:
  directional_light(const rgb& rad, const vec3& light_dir)
    : radiance(rad), dir_to_light((-1)*light_dir) {}

  rgb get_ray(vec3& p, vec3* dir_to_light, double* max_t) const;

private:
  vec3 dir_to_light;
  rgb radiance;
};

class point_light:public light {
public:
  point_light(const rgb& rad, const vec3& light_pos, const int falloff)
    : radiance(rad), pos(light_pos), falloff(falloff) {}

  rgb get_ray(vec3& p, vec3* dir_to_light, double* max_t) const;

private:
  vec3 pos;
  rgb radiance;
  int falloff;
};

#endif