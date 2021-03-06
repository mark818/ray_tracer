#include "triangle.h"

void triangle::get_barycentric_coordinate(const vec3 &p, double &u, double &v, double &w) const {
  vec3 p_minus_a = p - v1;
  double d00 = dot(v1v2, v1v2);
  double d01 = dot(v1v2, v1v3);
  double d11 = dot(v1v3, v1v3);
  double d20 = dot(p_minus_a, v1v2);
  double d21 = dot(p_minus_a, v1v3);
  double denom = d00 * d11 - d01 * d01;
  v = (d11 * d20 - d01 * d21) / denom;
  w = (d00 * d21 - d01 * d20) / denom;
  u = 1.0f - v - w;
}

bool triangle::intersect(const ray& r) const {
  const vec3 &n = normal; // normalized
 
  // Step 1: finding P
 
  // check if ray and plane are parallel ?
  double not_parallel = dot(n, r.d); 
  if (fabs(not_parallel) < 1e-31) // almost 0 
      return false; // they are parallel so they don't intersect ! 
 
  // compute d parameter using equation 2
  double d = -dot(n, v1); 
 
  // compute t (equation 3)
  double t = -(dot(n, r.o) + d) / not_parallel; 
  // check if the triangle is in behind the ray
  if (t <= 0 || t > r.max) return false; // the triangle is behind 
 
  // compute the intersection point using equation 1
  vec3 inter_p = r.o + t * r.d; 
 
  // Step 2: inside-outside test
  vec3 C; // vector perpendicular to triangle's plane 
 
  // edge 0
  vec3 edge1 = v2 - v1; 
  vec3 vp0 = inter_p - v1; 
  C = cross(edge1, vp0); 
  if (dot(n, C) < 0) return false; // P is on the right side 
 
  // edge 1
  vec3 edge2 = v3 - v2; 
  vec3 vp1 = inter_p - v2; 
  C = cross(edge2, vp1); 
  if (dot(n, C) < 0)  return false; // P is on the right side 
 
  // edge 2
  vec3 edge3 = v1 - v3; 
  vec3 vp2 = inter_p - v3; 
  C = cross(edge3, vp2); 
  if (dot(n, C) < 0) return false; // P is on the right side; 
 
  return true; // this ray hits the triangle 
}

  /**
   * Ray - Sphere intersection 2.
   * Check if the given ray intersects with the sphere, if so, the input
   * intersection data is updated to contain intersection information for the
   * point of intersection.
   * \param r ray to test intersection with
   * \param i address to store intersection info
   * \return true if the given ray intersects with the sphere,
             false otherwise
   */
bool triangle::intersect(const ray& r, intersection* i) const {
  const vec3 &n = normal; // normalized
 
  // Step 1: finding P
 
  // check if ray and plane are parallel ?
  double not_parallel = dot(n, r.d); 
  if (fabs(not_parallel) < 1e-31) // almost 0 
      return false; // they are parallel so they don't intersect ! 
 
  // compute d parameter using equation 2
  double d = - dot(n, v1); 
 
  // compute t (equation 3)
  double t = - (dot(n, r.o) + d) / not_parallel; 
  // check if the triangle is in behind the ray
  if (t <= 0) return false; // the triangle is behind 
 
  // compute the intersection point using equation 1
  vec3 inter_p = r.o + t * r.d; 
 
  // Step 2: inside-outside test
  vec3 C; // vector perpendicular to triangle's plane 
 
  // edge 0
  vec3 edge1 = v2 - v1; 
  vec3 vp0 = inter_p - v1; 
  C = cross(edge1, vp0); 
  if (dot(n, C) < 0) return false; // P is on the right side 
 
  // edge 1
  vec3 edge2 = v3 - v2; 
  vec3 vp1 = inter_p - v2; 
  C = cross(edge2, vp1); 
  if (dot(n, C) < 0)  return false; // P is on the right side 
 
  // edge 2
  vec3 edge3 = v1 - v3; 
  vec3 vp2 = inter_p - v3; 
  C = cross(edge3, vp2); 
  if (dot(n, C) < 0) return false; // P is on the right side; 
 
  double u, v, w;
  get_barycentric_coordinate(inter_p, u, v, w);
	i->t = t;
	i->p = this;
  i->n = (n1 * u + n2 * v + n3 * w).unit();

  return true; // this ray hits the triangle 
}
