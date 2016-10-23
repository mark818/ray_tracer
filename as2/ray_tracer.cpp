#include "ray_tracer.h"
#include "vec4.h"
#include <algorithm>
#include <thread>

using namespace std;

void ray_tracer::begin() {
  vector<thread> threads;
  threads.reserve(num_threads);
  size_t width_per_tile = static_cast<int>(my_camera.screen_w / num_threads);
  size_t height_per_tile = static_cast<int>(my_camera.screen_h / num_threads);
  for (int i = 0; i < num_threads; i++) {
    size_t left = width_per_tile * i;
    size_t right = min(width_per_tile * (i + 1), my_camera.screen_w);
    size_t top = height_per_tile * i;
    size_t bottom = min(height_per_tile * (i + 1), my_camera.screen_h);
    threads.emplace_back(&ray_tracer::worker, this, left, top, right, bottom);
  }
  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }
}

void ray_tracer::worker(size_t left, size_t top, size_t right, size_t bottom) {
  for (size_t j = top; j < bottom; j++) {
    for (size_t i = left; i < right; i++) {
      rgb color = shade_pixel(i, j);
      buffer[j * my_camera.screen_w + i] = color;
    }
  }
}

rgb ray_tracer::shade_pixel(size_t x, size_t y) {
  return rgb();
}

rgb ray_tracer::trace_ray(const ray &r) {
  rgb color;
  intersection i;

  if (!box.intersect(r, box.get_root(), &i)) {
    return color;
  }
  color += calc_direct_light(r, &i);
  color += calc_indrect_light(r, &i);
  return color;
}

rgb ray_tracer::calc_direct_light(const ray &r, intersection *i) {

  size_t depth = r.depth; // bounce level
  const vec3 &o = r.o; //origin
  const vec3 &d = r.d; //direction

  double t = i->t; //distance, length
  const primitive* p = i->p;
  vec3 &n = i->n; // normalized

	vec3 poi = o + t*d;
	poi = poi.unit();

	rgb radiance = { 0, 0, 0 };
	for (auto light : sc.lights) {

		vec3 dir_to_light;
		double max_t = 0;
		rgb I = light->get_ray(poi, &dir_to_light, &max_t);
		vec3 l = dir_to_light.unit();
		ray l_ray(poi, l, max_t);

		// wait for implementing in scene for bvh , ned to use bvh here to intersect
		if (!box.intersect(l_ray, box.get_root())) {

			vec3 r = ((-1.0)*l + (2.0*dot(l, n))*n).unit(); //reflected direction normal vector 
			vec3 v = -d; //view normal vector

			double sp = (p->ks).w;
			vec3 ks_vec3 = trim_to_vec3(p->ks);

			// where do we store ambient_l, right now it's in main
			rgb ambient = modmul(p->ka, (I + ambient_l));
			rgb diffuse = max(dot(l, n), 0.0)*modmul(p->kd, I);
			rgb specular = pow(max(dot(r, v), 0.0), sp)*modmul(ks_vec3, I);
			rgb col = ambient + diffuse + specular;
			radiance += col;
		}
	}
}
