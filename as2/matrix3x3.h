#ifndef MATRIX3X3
#define MATRIX3X3

#include "vec3.h"

/**
 * Defines a 3x3 matrix.
 * 3x3 matrices are extremely useful in computer graphics.
 */
class matrix3x3 {

  public:

  // The default constructor.
  matrix3x3(void) { }

  // Constructor for row major form data.
  // Transposes to the internal column major form.
  // REQUIRES: data should be of size 9 for a 3 by 3 matrix..
  matrix3x3(double * data)
  {
    for( int i = 0; i < 3; i++ ) {
      for( int j = 0; j < 3; j++ ) {
	        // Transpostion happens within the () query.
	        (*this)(i,j) = data[i*3 + j];
      }
    }
  }

  /**
   * Sets all elements to val.
   */
  void zero(double val = 0.0 );

  /**
   * Returns the determinant of A.
   */
  double det( void ) const;

  /**
   * Returns the Frobenius norm of A.
   */
  double norm( void ) const;

  /**
   * Returns the 3x3 identity matrix.
   */
  static matrix3x3 identity( void );

  /**
   * Returns a matrix representing the (left) cross product with u.
   */
  static matrix3x3 crossProduct( const vec3& u );

  /**
   * Returns the ith column.
   */
        vec3& column( int i );
  const vec3& column( int i ) const;

  /**
   * Returns the transpose of A.
   */
  matrix3x3 T( void ) const;

  /**
   * Returns the inverse of A.
   */
  matrix3x3 inv( void ) const;

  // accesses element (i,j) of A using 0-based indexing
        double& operator()( int i, int j );
  const double& operator()( int i, int j ) const;

  // accesses the ith column of A
        vec3& operator[]( int i );
  const vec3& operator[]( int i ) const;

  // increments by B
  void operator+=( const matrix3x3& B );

  // returns -A
  matrix3x3 operator-( void ) const;

  // returns A-B
  matrix3x3 operator-( const matrix3x3& B ) const;

  // returns c*A
  matrix3x3 operator*( double c ) const;

  // returns A*B
  matrix3x3 operator*( const matrix3x3& B ) const;

  // returns A*x
  vec3 operator*( const vec3& x ) const;

  // divides each element by x
  void operator/=( double x );

  protected:

  // column vectors
  vec3 entries[3];

}; // class matrix3x3

// returns the outer product of u and v
matrix3x3 outer( const vec3& u, const vec3& v );

// returns c*A
matrix3x3 operator*( double c, const matrix3x3& A );

// prints entries
std::ostream& operator<<( std::ostream& os, const matrix3x3& A );


#endif