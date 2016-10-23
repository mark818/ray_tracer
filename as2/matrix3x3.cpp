#include "matrix3x3.h"

#include <cmath>

double& matrix3x3::operator()( int i, int j ) {
  return entries[j][i];
}

const double& matrix3x3::operator()( int i, int j ) const {
  return entries[j][i];
}

vec3& matrix3x3::operator[]( int j ) {
  return entries[j];
}

const vec3& matrix3x3::operator[]( int j ) const {
  return entries[j];
}

void matrix3x3::zero( double val ) {
  // sets all elements to val
  entries[0] = entries[1] = entries[2] = vec3{ val, val, val };
}

double matrix3x3::det( void ) const {
  const matrix3x3& A( *this );

  return -A(0,2)*A(1,1)*A(2,0) + A(0,1)*A(1,2)*A(2,0) +
          A(0,2)*A(1,0)*A(2,1) - A(0,0)*A(1,2)*A(2,1) -
          A(0,1)*A(1,0)*A(2,2) + A(0,0)*A(1,1)*A(2,2) ;
}

double matrix3x3::norm( void ) const {
  return sqrt( entries[0].norm2() +
               entries[1].norm2() +
               entries[2].norm2() );
}

matrix3x3 matrix3x3::operator-( void ) const {

 // returns -A
  const matrix3x3& A( *this );
  matrix3x3 B;

  B(0,0) = -A(0,0); B(0,1) = -A(0,1); B(0,2) = -A(0,2);
  B(1,0) = -A(1,0); B(1,1) = -A(1,1); B(1,2) = -A(1,2);
  B(2,0) = -A(2,0); B(2,1) = -A(2,1); B(2,2) = -A(2,2);

  return B;
}

void matrix3x3::operator+=( const matrix3x3& B ) {

  matrix3x3& A( *this );
  double* Aij = (double*) &A;
  const double* Bij = (const double*) &B;

  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
  *Aij++ += *Bij++;
}

matrix3x3 matrix3x3::operator-( const matrix3x3& B ) const {
  const matrix3x3& A( *this );
  matrix3x3 C;

  for( int i = 0; i < 3; i++ )
  for( int j = 0; j < 3; j++ )
  {
     C(i,j) = A(i,j) - B(i,j);
  }

  return C;
}

matrix3x3 matrix3x3::operator+( const matrix3x3& B ) const {
  const matrix3x3& A( *this );
  matrix3x3 C;

  for( int i = 0; i < 3; i++ )
  for( int j = 0; j < 3; j++ )
  {
     C(i,j) = A(i,j) + B(i,j);
  }

  return C;
}

matrix3x3 matrix3x3::operator*( double c ) const {
  const matrix3x3& A( *this );
  matrix3x3 B;

  for( int i = 0; i < 3; i++ )
  for( int j = 0; j < 3; j++ )
  {
     B(i,j) = c*A(i,j);
  }

  return B;
}

matrix3x3 operator*( double c, const matrix3x3& A ) {

  matrix3x3 cA;
  const double* Aij = (const double*) &A;
  double* cAij = (double*) &cA;

  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);
  *cAij++ = c * (*Aij++);

  return cA;
}

matrix3x3 matrix3x3::operator*( const matrix3x3& B ) const {
  const matrix3x3& A( *this );
  matrix3x3 C;

  for( int i = 0; i < 3; i++ )
  for( int j = 0; j < 3; j++ )
  {
     C(i,j) = 0.;

     for( int k = 0; k < 3; k++ )
     {
        C(i,j) += A(i,k)*B(k,j);
     }
  }

  return C;
}

vec3 matrix3x3::operator*( const vec3& x ) const {
  return x[0]*entries[0] +
         x[1]*entries[1] +
         x[2]*entries[2] ;
}

matrix3x3 matrix3x3::T( void ) const {
  const matrix3x3& A( *this );
  matrix3x3 B;

  for( int i = 0; i < 3; i++ )
  for( int j = 0; j < 3; j++ )
  {
     B(i,j) = A(j,i);
  }

  return B;
}

matrix3x3 matrix3x3::inv( void ) const {
  const matrix3x3& A( *this );
  matrix3x3 B;

  B(0,0) = -A(1,2)*A(2,1) + A(1,1)*A(2,2); B(0,1) =  A(0,2)*A(2,1) - A(0,1)*A(2,2); B(0,2) = -A(0,2)*A(1,1) + A(0,1)*A(1,2);
  B(1,0) =  A(1,2)*A(2,0) - A(1,0)*A(2,2); B(1,1) = -A(0,2)*A(2,0) + A(0,0)*A(2,2); B(1,2) =  A(0,2)*A(1,0) - A(0,0)*A(1,2);
  B(2,0) = -A(1,1)*A(2,0) + A(1,0)*A(2,1); B(2,1) =  A(0,1)*A(2,0) - A(0,0)*A(2,1); B(2,2) = -A(0,1)*A(1,0) + A(0,0)*A(1,1);

  B /= det();

  return B;
}

void matrix3x3::operator/=( double x ) {
  matrix3x3& A( *this );
  double rx = 1./x;

  for( int i = 0; i < 3; i++ )
  for( int j = 0; j < 3; j++ )
  {
     A( i, j ) *= rx;
  }
}

matrix3x3 matrix3x3::identity( void ) {
  matrix3x3 B;

  B(0,0) = 1.; B(0,1) = 0.; B(0,2) = 0.;
  B(1,0) = 0.; B(1,1) = 1.; B(1,2) = 0.;
  B(2,0) = 0.; B(2,1) = 0.; B(2,2) = 1.;

  return B;
}

matrix3x3 matrix3x3::crossProduct( const vec3& u ) {
  matrix3x3 B;

  B(0,0) =   0.;  B(0,1) = -u.z;  B(0,2) =  u.y;
  B(1,0) =  u.z;  B(1,1) =   0.;  B(1,2) = -u.x;
  B(2,0) = -u.y;  B(2,1) =  u.x;  B(2,2) =   0.;

  return B;
}

matrix3x3 outer( const vec3& u, const vec3& v ) {
  matrix3x3 B;
  double* Bij = (double*) &B;

  *Bij++ = u.x*v.x;
  *Bij++ = u.y*v.x;
  *Bij++ = u.z*v.x;
  *Bij++ = u.x*v.y;
  *Bij++ = u.y*v.y;
  *Bij++ = u.z*v.y;
  *Bij++ = u.x*v.z;
  *Bij++ = u.y*v.z;
  *Bij++ = u.z*v.z;

  return B;
}

std::ostream& operator<<( std::ostream& os, const matrix3x3& A ) {
  for( int i = 0; i < 3; i++ )
  {
     os << "[ ";

     for( int j = 0; j < 3; j++ )
     {
        os << A(i,j) << " ";
     }

     os << "]" << std::endl;
  }

  return os;
}

vec3& matrix3x3::column( int i ) {
  return entries[i];
}

const vec3& matrix3x3::column( int i ) const {
  return entries[i];
}
