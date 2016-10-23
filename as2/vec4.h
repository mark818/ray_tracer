#ifndef VEC4
#define VEC4
#include "vec3.h"

struct vec4 {
	double x, y, z, w;

	vec4 operator-(void) const {
		return vec4{ -x, -y, -z, -w };
	}

	vec4 operator+(const vec4& v) const {
		 return vec4{ x + v.x, y + v.y, z + v.z, w + v.w };
	}

	vec4 operator-(const vec4& v) const {
		 return vec4{ x - v.x, y - v.y, z - v.z, w - v.w };
	}

	vec4 operator*(const double& c) const {
		 return vec4{ x * c, y * c, z * c, w * c };
	}

	vec4 operator/(const double& c) const {
		const double rc = 1.0 / c;
		return vec4{ rc * x, rc * y, rc * z, rc * w };
	}

	void operator+=(const vec4& v) {
		x += v.x; y += v.y; z += v.z; z += v.w;
	}

	void operator-=(const vec4& v) {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
	}

	void operator*=(const double& c) {
		x *= c; y *= c; z *= c; w *= c;
	}

	void operator/=(const double& c) {
		(*this) *= (1. / c);
	}

	double norm(void) const {
		return sqrt(x*x + y*y + z*z + w*w);
	}

	inline double norm2(void) const {
		return x*x + y*y + z*z + w*w;
	}

	vec4 unit(void) const {
		double rNorm = 1. / sqrt(x*x + y*y + z*z + w*w);
		return vec4{ rNorm*x, rNorm*y, rNorm*z };
	}

	double& operator[] (const int& index) {
		return (&x)[index];
	}

	const double& operator[] (const int& index) const {
		return (&x)[index];
	}
};

inline vec4 operator* (const double& c, const vec4& v) {
		return vec4{ c * v.x, c * v.y, c * v.z, c*v.w };
	}

inline double dot(const vec4& u, const vec4& v) {
		return u.x*v.x + u.y*v.y + u.z*v.z + u.w*v.w;;
	}

inline vec3 trim_to_vec3(vec4& v) {
		return vec3{v.x, v.y, v.z};
	}

inline vec3 trim_to_vec3(vec4&& v) {
		return vec3{v.x, v.y, v.z};
	}

#endif

