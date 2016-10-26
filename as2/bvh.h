#ifndef BVH
#define BVH
#include "aabb.h"
#include "intersection.h"

class bvh {
public:

  bvh(const std::vector<primitive*> &primitives) {
    root = recursive_split(primitives, 1);
  }

  aabb* get_root();

  aabb* recursive_split(const std::vector<primitive*> &primitives, unsigned int max_leaf);

  bool intersect(const ray& r, aabb* node);

  bool intersect(const ray& r, aabb* node, intersection *i);

private:
  aabb* root;
  /* data */
};

#endif