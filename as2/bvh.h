#ifndef BVH
#define BVH
#include "aabb.h"
#include "intersection.h"

class bvh {
public:

  bvh(const std::vector<primitive*> &primitives, int max_leaf);
 

  aabb* get_root();

  aabb* recursive_split(const std::vector<primitive*> &primitives);

  bool intersect(const ray& r, aabb* node, const primitive *p);

  bool intersect(const ray& r, aabb* node, intersection *i);

private:
  aabb* root;
  int max_leaf = 2;
  /* data */
};

#endif