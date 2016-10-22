#ifndef INTERSECTION 
#define INTERSECTION
#include "vec3.h"

class primitive;

struct intersection {
  double t;
  const primitive* p;
  // normalized
  vec3 n;
};
#endif