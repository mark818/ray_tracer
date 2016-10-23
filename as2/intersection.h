#ifndef INTERSECTION 
#define INTERSECTION
#include "vec3.h"

class primitive;

struct intersection {
  double t;
  const primitive* p;
  vec3 n; // normalized
};
#endif