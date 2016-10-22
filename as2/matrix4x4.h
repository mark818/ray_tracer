#ifndef CGL_matrix4X4_H
#define CGL_matrix4X4_H

#include "vec4.h"

class matrix4x4 {
public:
  matrix4x4() {}

  void zero(double val = 0.0);
  double det() const;
  double norm() const;
  static matrix4x4 identity();

  vec4& column(int i);
  const vec4& column(int i) const;

  matrix4x4 transpose() const;
  matrix4x4 inv() const;

  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

  vec4& operator[](int i);
  const vec4& operator[](int i) const;

  void operator+=(const matrix4x4& B);

  matrix4x4 operator-() const;
  matrix4x4 operator-(const matrix4x4& B) const;
  matrix4x4 operator*(double c) const;
  matrix4x4 operator*(const matrix4x4& B) const;
  vec4 operator*(const vec4& x) const;
  void operator/=(double x);

private:
  vec4 entries[4];
};

matrix4x4 outer(const vec4& u, const vec4& v);
matrix4x4 operator*(double c, const matrix4x4& A);

#endif 