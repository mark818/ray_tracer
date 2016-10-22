#ifndef RAY_TRACER
#define RAY_TRACER
#include "light.h"
#include "camera.h"
#include "image_buffer.h"
class ray_tracer {
public:
  ray_tracer();
  ~ray_tracer() = default;

  ray_tracer(const ray_tracer&) = delete;
  ray_tracer& operator =(const ray_tracer&) = delete;

private:
  camera cam;
  image_buffer buffer;
  int msaa = 1;
};
#endif

