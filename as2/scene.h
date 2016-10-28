#ifndef SCENE
#define SCENE
#include <vector>
#include "vec4.h"
#include "ray.h"
#include "intersection.h"
#include "aabb.h"

class primitive {
public:
  primitive(vec3 ka, vec3 kd, vec4 ks, vec3 kr) :
    ka(ka), kd(kd), ks(ks), kr(kr) {}

  virtual aabb get_aabb() const = 0;

  virtual bool intersect(const ray& r) const = 0;

  /**
   * Check if the given ray intersects with the primitive, if so, the input
   * intersection data is updated to contain intersection information for the
   * point of intersection.
   * \param r ray to test intersection with
   * \param i address to store intersection info
   * \return true if the given ray intersects with the primitive,
             false otherwise
   */
  virtual bool intersect(const ray& r, intersection* i) const = 0;

  vec3 ka;
  vec3 kd;
  vec4 ks;
  vec3 kr;
};

/**
 * Interface for lights in the scene.
 */
 class light {
 public:
   virtual rgb get_ray(const vec3& p, vec3* wi, double* max_t) const = 0;

 };

 struct scene {
   scene() {}

   scene(const std::vector<primitive *>& primitives, const std::vector<light *>& lights, rgb &ambient_l)
     : primitives(primitives), lights(lights), ambient_l(ambient_l) {}

   scene(const scene &&rhs) : primitives(std::move(rhs.primitives)), lights(std::move(rhs.lights)), ambient_l(std::move(rhs.ambient_l)) {}

   std::vector<primitive*> primitives;
   std::vector<light*> lights;
   rgb ambient_l;
 };

#endif