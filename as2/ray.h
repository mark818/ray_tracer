#ifndef ray
#define ray
#include "vec3.h"
struct ray {
	size_t depth;  
	vec3 o, d; 
	mutable double min, max;
	vec3 inv_d; 
	int sign[3]; 

	ray(const vec3& o, const vec3& d, int depth = 0)
		: o(o), d(d), min_t(0.0), max_t(INF_D), depth(depth) {
		inv_d = vec3(1 / d.x, 1 / d.y, 1 / d.z);
		sign[0] = (inv_d.x < 0);
		sign[1] = (inv_d.y < 0);
		sign[2] = (inv_d.z < 0);
	}

	/**
	* Constructor.
	* Create a ray instance with given origin and direction.
	* \param o origin of the ray
	* \param d direction of the ray
	* \param max_t max t value for the ray (if it's actually a segment)
	* \param depth depth of the ray
	*/
	ray(const vec3& o, const vec3& d, double max_t, int depth = 0)
		: o(o), d(d), min_t(0.0), max_t(max_t), depth(depth) {
		inv_d = vec3(1 / d.x, 1 / d.y, 1 / d.z);
		sign[0] = (inv_d.x < 0);
		sign[1] = (inv_d.y < 0);
		sign[2] = (inv_d.z < 0);
	}


	/**
	* Returns the point t * |d| along the ray.
	*/
	inline vec3 at_time(double t) const { return o + t * d; }

	/**
	* Returns the result of transforming the ray by the given transformation
	* matrix.
	*/
	ray transform_by(const Matrix4x4& t) const {
		const Vector4D& newO = t * Vector4D(o, 1.0);
		return ray((newO / newO.w).to3D(), (t * Vector4D(d, 0.0)).to3D());
	}
};

#endif

