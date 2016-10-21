#ifndef VEC3
#define VEC3
#include <math.h>
#include <utility>
#include <iostream>

template <typename T>
inline T sqr(T arg) {
	return arg * arg;
}

struct vec3 {
	double x, y, z;

	vec3& operator+= (vec3 &v) {
		return (*this) += std::move(v);
	}

	vec3& operator+= (vec3 &&v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& operator-= (const vec3 &v) {
		return (*this) -= std::move(v);
	}

	vec3& operator-= (const vec3 &&v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3 operator- () {
		return vec3{ -x, -y, -z };
	}

	vec3& operator*= (const double f) {
		x *= f;
		y *= f;
		z *= f;
	}

	vec3& operator/= (const double f) {
		if (f == 0) {
			std::cerr << "Vector Division by 0\n";
			exit(1);
		}
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	vec3 operator+ (const vec3& v) const {
		return (*this) + std::move(v);
	}

	vec3 operator+ (const vec3&& v) const {
		return vec3{ x + v.x, y + v.y, z + v.z };
	}

	vec3 operator- (const vec3& v) const {
		return (*this) - std::move(v);
	}

	vec3 operator- (const vec3&& v) const {
		return vec3{ x - v.x, y - v.y, z - v.z };
	}

	vec3 operator* (const double d) const {
		return vec3{ x * d, y * d, z * d };
	}

	vec3 operator/ (const double d) const {
		return vec3{ x / d, y / d, z / d };
	}

	bool operator== (const vec3&& v) const {
		return x == v.x && y == v.y && z == v.z;
	}

	double norm() const {
		return sqrt(x*x + y*y + z*z);
	}

	vec3 unit() const {
		double product = sqrt(sqr(x) + sqr(y) + sqr(z));
		return vec3{ x / product, y / product, z / product };
	}
};

inline double dot(vec3 &v1, vec3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vec3 modmul(vec3 &v1, vec3 &v2) {
	return{ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

inline vec3 cross(vec3 &v1, vec3 &v2) {
	return{ v1.y * v2.z - v2.y * v1.z, -v1.x * v2.z + v2.x * v1.z, v1.x * v2.y - v2.x * v1.y };
}

inline vec3 operator* (const double& c, const vec3& v) {
	return v * c;
}

using rgb = vec3;

#endif