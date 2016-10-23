#ifndef RAY_TRACER
#define RAY_TRACER
#include <string>
#include <mutex>
#include "light.h"
#include "camera.h"
#include "scene.h"
#include "bvh.h"
#include "image_buffer.h"

class ray_tracer {
public:

  ray_tracer(camera &my_camera, scene &sc, string &filename) 
  	: my_camera(std::move(my_camera)), sc(std::move(sc)), 
  		buffer(my_camera.screen_w, my_camera.screen_h), filename(filename) {
    box.recursive_split(sc.primitives, 5);
  }
  ~ray_tracer() = default;

  void begin();
  
  ray_tracer(const ray_tracer&) = delete;
  ray_tracer& operator =(const ray_tracer&) = delete;

private:
  void test();
	void worker(size_t left, size_t top, size_t right, size_t bottom);
	rgb shade_pixel(size_t x, size_t y);
	rgb trace_ray(const ray &r);
	rgb calc_direct_light(const ray &r, intersection *i);
	rgb calc_indrect_light(const ray &r, intersection *i);

  camera my_camera;
  scene sc;
  bvh box;
  image_buffer buffer;
  string filename;
  int num_threads = 8;
  std::mutex lock, done;
  int msaa = 1;
};
#endif

