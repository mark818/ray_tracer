#ifndef RAY_TRACER
#define RAY_TRACER
#include <string>
#include "light.h"
#include "camera.h"
#include "scene.h"
#include "image_buffer.h"

class ray_tracer {
public:

  ray_tracer(camera &my_camera, scene &sc, string &filename) 
  	: my_camera(std::move(my_camera)), sc(std::move(sc)), 
  		buffer(my_camera.screen_w, my_camera.screen_h), filename(filename) {}
  ~ray_tracer() = default;

  void begin();

  ray_tracer(const ray_tracer&) = delete;
  ray_tracer& operator =(const ray_tracer&) = delete;

private:

	void worker();
	rgb shade_pixel(unsigned int x, unsigned int y);
	rgb trace_ray(const ray &r);
	rgb calc_direct_light(const ray &r, intersection *i);
	rgb calc_indrect_light(const ray &r, intersection *i);

  camera my_camera;
  scene sc;
  image_buffer buffer;
  string filename;
  int msaa = 1;
};
#endif

