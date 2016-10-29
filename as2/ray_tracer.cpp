#include <algorithm>
#include <thread>
#include <cmath>
#include <time.h>
#include <iostream>
#include "ray_tracer.h"
#include "vec4.h"

using namespace std;

void ray_tracer::begin() {
  if (my_camera.has_dof())
    this->shade_method = &ray_tracer::shade_with_depth;
  clock_t time = clock();
  dispatch();
  time = clock() - time;
  cout << "Time taken to render with " << num_threads << " threads: " << time << "ms\n";
  buffer.write_to_png(filename.c_str());
}

void ray_tracer::dispatch() {
  vector<thread> threads;
  threads.reserve(num_threads);
  size_t height_per_tile = static_cast<int>(my_camera.screen_h / num_threads);
  for (int i = 0; i < num_threads; i++) {
    size_t top = height_per_tile * i;
    size_t bottom = min(height_per_tile * (i + 1), my_camera.screen_h);
    threads.emplace_back(&ray_tracer::worker, this, 0, top, my_camera.screen_w, bottom);
  }
  for (int i = 0; i < num_threads; i++) {
    threads[i].join();
  }
}

void ray_tracer::worker(size_t left, size_t top, size_t right, size_t bottom) {
    for (size_t j = top; j < bottom; j++) {
      for (size_t i = left; i < right; i++) {
        rgb color = (this->*shade_method)(i, j);
        const vec3 v;
        buffer.set(i, j, color);
      }
    }
}


rgb ray_tracer::shade_pixel(size_t x, size_t y) {
  double sqrt_msaa = sqrt(msaa);
  rgb color(0, 0, 0);
  for (int i = 0; i < sqrt_msaa; ++i) {
    for (int j = 0; j < sqrt_msaa; ++j) {
      double u = (x + (i/sqrt_msaa))/my_camera.screen_w;
      double v = (y + (j/sqrt_msaa))/my_camera.screen_h;
      ray r = my_camera.generate_ray(u, v);
      r.depth = depth;
      color += trace_ray(r);
    }
  }
  // if (color.z > 0) { 
  // printf("get pixel's color: %zu %zu: %f %f %f\n", x, y, color.x, color.y, color.z);
  // }
  return (color/msaa);
}


rgb ray_tracer::shade_with_depth(size_t x, size_t y) {
  double sqrt_msaa = sqrt(msaa);
  rgb color(0, 0, 0);
  for (int i = 0; i < sqrt_msaa; ++i) {
    for (int j = 0; j < sqrt_msaa; ++j) {
      double u = (x + (i / sqrt_msaa)) / my_camera.screen_w;
      double v = (y + (j / sqrt_msaa)) / my_camera.screen_h;
      vector<ray> bundle = my_camera.generate_ray_bundle(u, v);
      for (ray r : bundle) {
        r.depth = depth;
        color += trace_ray(r);
      }
    }
  }
  return color / (msaa * 9);
}

// ray here is like eye ray
rgb ray_tracer::trace_ray(const ray &r) {
 // printf("ray.o: %f %f %f  ray.d %f %f %f\n", r.o.x, r.o.y, r.o.z, r.d.x, r.d.y, r.d.z);
  rgb color(0, 0, 0);
  intersection i;

  if (!box.intersect(r, box.get_root(), &i)) {
    return color;
  }
  color += calc_direct_light(r, &i);  
  if (r.depth > 0) {
    color += calc_indrect_light(r, &i);
  }
  // printf("get pixel's color: %f %f %f\n", color.x, color.y, color.z);
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

	rgb radiance(0, 0, 0);
	for (auto light : sc.lights) {

		vec3 dir_to_light;
		double max_t = 0;
		rgb I = light->get_ray(poi, &dir_to_light, &max_t);
		vec3 l = dir_to_light.unit();
		ray l_ray(poi, l, max_t);

		if (!box.intersect(l_ray, box.get_root(), p)) {

			vec3 r = ((-1.0)*l + (2.0*dot(l, n))*n).unit(); //reflected direction normal vector 
			vec3 v = -d; //view normal vector

			double sp = (p->ks).w;
			vec3 ks_vec3 = trim_to_vec3(p->ks);
      rgb ambient;
      if (sc.ambient_l.norm() > 0) {
        ambient = modmul(p->ka, sc.ambient_l);
      } else {
        ambient = modmul(p->ka, I);
      }

      rgb diffuse = max(dot(l, n), 0.0)*modmul(p->kd, I);
			rgb specular = pow(max(dot(r, v), 0.0), sp)*modmul(ks_vec3, I);
			rgb col = ambient + diffuse + specular;
			radiance += col;
		}
	}
  return radiance;
}

rgb ray_tracer::calc_indrect_light(const ray &r, intersection *i) {
  size_t depth = r.depth; // bounce level
  const vec3 &o = r.o; //origin
  const vec3 &d = r.d; //direction

  double t = i->t; //distance, length
  const primitive* p = i->p;
  vec3 &n = i->n; // normalized
  // printf("t: %f  n: %f %f %f\n", t, n.x, n.y, n.z);
  vec3 l = (-d).unit();
  vec3 poi = o + t*d;
  vec3 out = ((-1.0)*l + (2.0*dot(l, n))*n).unit(); //normalized
  ray more_r(poi + 1e-5 * out, out, depth-1);
  rgb color = trace_ray(more_r);

  rgb radiance = modmul(color, p->kr);
  return radiance;
}

