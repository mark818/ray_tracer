#include "matrix4x4.h"

#include <math.h>

// first entry is the first column
double& matrix4x4::operator()(int i, int j) {
  return entries[j][i];
}

const double& matrix4x4::operator()(int i, int j) const {
  return entries[j][i];
}


vec4& matrix4x4::column(int i) {
  return entries[i];
}

const vec4& matrix4x4::column(int i) const {
  return entries[i];
}

void matrix4x4::zero(double val) {
  // sets all elements to val
  entries[0] =
  entries[1] =
  entries[2] =
  entries[3] = vec4{ val, val, val, val };
}

double matrix4x4::det() const {
  const matrix4x4& A(*this);

  return
    A(0, 3)*A(1, 2)*A(2, 1)*A(3, 0) - A(0, 2)*A(1, 3)*A(2, 1)*A(3, 0) -
    A(0, 3)*A(1, 1)*A(2, 2)*A(3, 0) + A(0, 1)*A(1, 3)*A(2, 2)*A(3, 0) +
    A(0, 2)*A(1, 1)*A(2, 3)*A(3, 0) - A(0, 1)*A(1, 2)*A(2, 3)*A(3, 0) -
    A(0, 3)*A(1, 2)*A(2, 0)*A(3, 1) + A(0, 2)*A(1, 3)*A(2, 0)*A(3, 1) +
    A(0, 3)*A(1, 0)*A(2, 2)*A(3, 1) - A(0, 0)*A(1, 3)*A(2, 2)*A(3, 1) -
    A(0, 2)*A(1, 0)*A(2, 3)*A(3, 1) + A(0, 0)*A(1, 2)*A(2, 3)*A(3, 1) +
    A(0, 3)*A(1, 1)*A(2, 0)*A(3, 2) - A(0, 1)*A(1, 3)*A(2, 0)*A(3, 2) -
    A(0, 3)*A(1, 0)*A(2, 1)*A(3, 2) + A(0, 0)*A(1, 3)*A(2, 1)*A(3, 2) +
    A(0, 1)*A(1, 0)*A(2, 3)*A(3, 2) - A(0, 0)*A(1, 1)*A(2, 3)*A(3, 2) -
    A(0, 2)*A(1, 1)*A(2, 0)*A(3, 3) + A(0, 1)*A(1, 2)*A(2, 0)*A(3, 3) +
    A(0, 2)*A(1, 0)*A(2, 1)*A(3, 3) - A(0, 0)*A(1, 2)*A(2, 1)*A(3, 3) -
    A(0, 1)*A(1, 0)*A(2, 2)*A(3, 3) + A(0, 0)*A(1, 1)*A(2, 2)*A(3, 3);

}

double matrix4x4::norm() const {
  return sqrt(entries[0].norm2() +
    entries[1].norm2() +
    entries[2].norm2() +
    entries[3].norm2());
}

matrix4x4 matrix4x4::operator-() const {

  // returns -A (Negation).
  const matrix4x4& A(*this);
  matrix4x4 B;

  B(0, 0) = -A(0, 0); B(0, 1) = -A(0, 1); B(0, 2) = -A(0, 2); B(0, 3) = -A(0, 3);
  B(1, 0) = -A(1, 0); B(1, 1) = -A(1, 1); B(1, 2) = -A(1, 2); B(1, 3) = -A(1, 3);
  B(2, 0) = -A(2, 0); B(2, 1) = -A(2, 1); B(2, 2) = -A(2, 2); B(2, 3) = -A(2, 3);
  B(3, 0) = -A(3, 0); B(3, 1) = -A(3, 1); B(3, 2) = -A(3, 2); B(3, 3) = -A(3, 3);

  return B;
}

void matrix4x4::operator+=(const matrix4x4& B) {

  matrix4x4& A(*this);
  double* Aij = (double*)&A;
  const double* Bij = (const double*)&B;

  // Add the 16 contigous vector packed double values.
  *Aij++ += *Bij++;//0
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;//4
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;//8
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;//12
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;//15
            //16.

}

matrix4x4 matrix4x4::operator-(const matrix4x4& B) const {
  const matrix4x4& A(*this);
  matrix4x4 C;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      C(i, j) = A(i, j) - B(i, j);
    }

  return C;
}

matrix4x4 matrix4x4::operator+(const matrix4x4& B) const {
  const matrix4x4& A(*this);
  matrix4x4 C;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      C(i, j) = A(i, j) + B(i, j);
    }

  return C;
}

matrix4x4 matrix4x4::operator*(double c) const {
  const matrix4x4& A(*this);
  matrix4x4 B;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      B(i, j) = c*A(i, j);
    }

  return B;
}

// Returns c*A.
matrix4x4 operator*(double c, const matrix4x4& A) {

  matrix4x4 cA;
  const double* Aij = (const double*)&A;
  double* cAij = (double*)&cA;

  *cAij++ = c * (*Aij++);//0
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);//4
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);//8
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);//12
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);//15
              //16
  return cA;
}

// Tradiational Grade School Multiplication. N^3
matrix4x4 matrix4x4::operator*(const matrix4x4& B) const {
  const matrix4x4& A(*this);
  matrix4x4 C;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      C(i, j) = 0.;

      for (int k = 0; k < 4; k++) {
        C(i, j) += A(i, k)*B(k, j);
      }
    }

  return C;
}


vec4 matrix4x4::operator*(const vec4& x) const {
  return x[0] * entries[0] + // Add up products for each matrix column.
         x[1] * entries[1] +
         x[2] * entries[2] +
         x[3] * entries[3];
}

// Naive Transposition.
matrix4x4 matrix4x4::T() const {
  const matrix4x4& A(*this);
  matrix4x4 B;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      B(i, j) = A(j, i);
    }

  return B;
}

matrix4x4 matrix4x4::inv() const {
  const matrix4x4& A(*this);
  matrix4x4 B;

  // Hardcoded in Fully Symbolic computation.

  B(0, 0) = A(1, 2)*A(2, 3)*A(3, 1) - A(1, 3)*A(2, 2)*A(3, 1) + A(1, 3)*A(2, 1)*A(3, 2) - A(1, 1)*A(2, 3)*A(3, 2) - A(1, 2)*A(2, 1)*A(3, 3) + A(1, 1)*A(2, 2)*A(3, 3);
  B(0, 1) = A(0, 3)*A(2, 2)*A(3, 1) - A(0, 2)*A(2, 3)*A(3, 1) - A(0, 3)*A(2, 1)*A(3, 2) + A(0, 1)*A(2, 3)*A(3, 2) + A(0, 2)*A(2, 1)*A(3, 3) - A(0, 1)*A(2, 2)*A(3, 3);
  B(0, 2) = A(0, 2)*A(1, 3)*A(3, 1) - A(0, 3)*A(1, 2)*A(3, 1) + A(0, 3)*A(1, 1)*A(3, 2) - A(0, 1)*A(1, 3)*A(3, 2) - A(0, 2)*A(1, 1)*A(3, 3) + A(0, 1)*A(1, 2)*A(3, 3);
  B(0, 3) = A(0, 3)*A(1, 2)*A(2, 1) - A(0, 2)*A(1, 3)*A(2, 1) - A(0, 3)*A(1, 1)*A(2, 2) + A(0, 1)*A(1, 3)*A(2, 2) + A(0, 2)*A(1, 1)*A(2, 3) - A(0, 1)*A(1, 2)*A(2, 3);
  B(1, 0) = A(1, 3)*A(2, 2)*A(3, 0) - A(1, 2)*A(2, 3)*A(3, 0) - A(1, 3)*A(2, 0)*A(3, 2) + A(1, 0)*A(2, 3)*A(3, 2) + A(1, 2)*A(2, 0)*A(3, 3) - A(1, 0)*A(2, 2)*A(3, 3);
  B(1, 1) = A(0, 2)*A(2, 3)*A(3, 0) - A(0, 3)*A(2, 2)*A(3, 0) + A(0, 3)*A(2, 0)*A(3, 2) - A(0, 0)*A(2, 3)*A(3, 2) - A(0, 2)*A(2, 0)*A(3, 3) + A(0, 0)*A(2, 2)*A(3, 3);
  B(1, 2) = A(0, 3)*A(1, 2)*A(3, 0) - A(0, 2)*A(1, 3)*A(3, 0) - A(0, 3)*A(1, 0)*A(3, 2) + A(0, 0)*A(1, 3)*A(3, 2) + A(0, 2)*A(1, 0)*A(3, 3) - A(0, 0)*A(1, 2)*A(3, 3);
  B(1, 3) = A(0, 2)*A(1, 3)*A(2, 0) - A(0, 3)*A(1, 2)*A(2, 0) + A(0, 3)*A(1, 0)*A(2, 2) - A(0, 0)*A(1, 3)*A(2, 2) - A(0, 2)*A(1, 0)*A(2, 3) + A(0, 0)*A(1, 2)*A(2, 3);
  B(2, 0) = A(1, 1)*A(2, 3)*A(3, 0) - A(1, 3)*A(2, 1)*A(3, 0) + A(1, 3)*A(2, 0)*A(3, 1) - A(1, 0)*A(2, 3)*A(3, 1) - A(1, 1)*A(2, 0)*A(3, 3) + A(1, 0)*A(2, 1)*A(3, 3);
  B(2, 1) = A(0, 3)*A(2, 1)*A(3, 0) - A(0, 1)*A(2, 3)*A(3, 0) - A(0, 3)*A(2, 0)*A(3, 1) + A(0, 0)*A(2, 3)*A(3, 1) + A(0, 1)*A(2, 0)*A(3, 3) - A(0, 0)*A(2, 1)*A(3, 3);
  B(2, 2) = A(0, 1)*A(1, 3)*A(3, 0) - A(0, 3)*A(1, 1)*A(3, 0) + A(0, 3)*A(1, 0)*A(3, 1) - A(0, 0)*A(1, 3)*A(3, 1) - A(0, 1)*A(1, 0)*A(3, 3) + A(0, 0)*A(1, 1)*A(3, 3);
  B(2, 3) = A(0, 3)*A(1, 1)*A(2, 0) - A(0, 1)*A(1, 3)*A(2, 0) - A(0, 3)*A(1, 0)*A(2, 1) + A(0, 0)*A(1, 3)*A(2, 1) + A(0, 1)*A(1, 0)*A(2, 3) - A(0, 0)*A(1, 1)*A(2, 3);
  B(3, 0) = A(1, 2)*A(2, 1)*A(3, 0) - A(1, 1)*A(2, 2)*A(3, 0) - A(1, 2)*A(2, 0)*A(3, 1) + A(1, 0)*A(2, 2)*A(3, 1) + A(1, 1)*A(2, 0)*A(3, 2) - A(1, 0)*A(2, 1)*A(3, 2);
  B(3, 1) = A(0, 1)*A(2, 2)*A(3, 0) - A(0, 2)*A(2, 1)*A(3, 0) + A(0, 2)*A(2, 0)*A(3, 1) - A(0, 0)*A(2, 2)*A(3, 1) - A(0, 1)*A(2, 0)*A(3, 2) + A(0, 0)*A(2, 1)*A(3, 2);
  B(3, 2) = A(0, 2)*A(1, 1)*A(3, 0) - A(0, 1)*A(1, 2)*A(3, 0) - A(0, 2)*A(1, 0)*A(3, 1) + A(0, 0)*A(1, 2)*A(3, 1) + A(0, 1)*A(1, 0)*A(3, 2) - A(0, 0)*A(1, 1)*A(3, 2);
  B(3, 3) = A(0, 1)*A(1, 2)*A(2, 0) - A(0, 2)*A(1, 1)*A(2, 0) + A(0, 2)*A(1, 0)*A(2, 1) - A(0, 0)*A(1, 2)*A(2, 1) - A(0, 1)*A(1, 0)*A(2, 2) + A(0, 0)*A(1, 1)*A(2, 2);

  // Invertable iff the determinant is not equal to zero.
  B /= det();

  return B;
}

void matrix4x4::operator/=(double x) {
  matrix4x4& A(*this);
  double rx = 1. / x;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      A(i, j) *= rx;
    }
}

matrix4x4 matrix4x4::identity() {
  matrix4x4 B;

  B(0, 0) = 1.; B(0, 1) = 0.; B(0, 2) = 0.; B(0, 3) = 0.;
  B(1, 0) = 0.; B(1, 1) = 1.; B(1, 2) = 0.; B(1, 3) = 0.;
  B(2, 0) = 0.; B(2, 1) = 0.; B(2, 2) = 1.; B(2, 3) = 0.;
  B(3, 0) = 0.; B(3, 1) = 0.; B(3, 2) = 0.; B(3, 3) = 1.;

  return B;
}

matrix4x4 outer(const vec4& u, const vec4& v) {
  matrix4x4 B;

  // Opposite of an inner product.
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      B(i, j) = u[i] * v[j];
    }

  return B;
}



matrix4x4 extend_to_matrix4x4(const matrix3x3& m) {
  matrix4x4 m4;

  m4.column(0) = vec4{m(0, 0), m(1, 0), m(2, 0), 0};
  m4.column(1) = vec4{m(0, 1), m(1, 1), m(2, 1), 0};
  m4.column(2) = vec4{m(0, 2), m(1, 2), m(2, 2), 0};
  m4.column(3) = vec4{0, 0, 0, 1};

  return m4;
}
