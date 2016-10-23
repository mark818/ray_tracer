#include "ray_tracer.h"
#include "vec4.h"

ray_tracer::ray_tracer() {}

rgb ray_tracer::calc_direct_light(const ray &r, intersection *i) {

  size_t depth = r.depth; // bounce level
  vec3 &o = r.o; //origin
  vec3 &d = r.d; //direction

  double t = i->t; //distance, length
  const primitive* p = i->p;
  vec3 &n = i->n; // normalized

	vec3 poi = o + t*d;
	poi = poi.unit();

	rgb radiance = { 0, 0, 0 };
	for (auto light : sc.lights) {

		vec3 dir_to_light;
		double max_t = 0;
		rgb I = get_ray(poi, &dir_to_light, &max_t);
		vec3 l = dir_to_light.unit();
		ray l_ray(poi, l, max_t);

		// wait for implementing in scene for bvh , ned to use bvh here to intersect
		if (!bvh->intersect(l_ray)) {

			vec3 r = ((-1.0)*l + (2.0*dot(l, n))*n).unit(); //reflected direction normal vector 
			vec3 v = -d; //view normal vector

			double sp = (light->ks).w;
			vec3 ks_vec3 = trim_to_vec3(light->ks);

			// where do we store ambient_l, right now it's in main
			rgb ambient = modmul(light.ka, (I + ambient_l));
			rgb diffuse = max(dot(l, n), 0.0)*modmul(light.kd, I);
			rgb specular = pow(max(dot(r, v), 0.0), sp)*modmul(ks_vec3, I);
			rgb col = ambient + diffuse + specular;
			radiance += col;
		}
	}
}
