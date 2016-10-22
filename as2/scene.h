#ifndef SCENE
#define SCENE
#include "vector"
#include "vec3.h"
#include "ray.h"
#include "intersection.h"
#include "aabb.h"

class primitive {
public:
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

};

/**
 * Interface for lights in the scene.
 */
class light {
public:
    virtual rgb get_ray(vec3& p, vec3* wi, double* max_t) const = 0;

};

struct scene {
    scene(const std::vector<primitive *>& primitives,
          const std::vector<light *>& lights)
    : primitives(primitives), lights(lights) { }

    std::vector<primitive*> primitives;

    std::vector<light*> lights;
};

#endif