#include <vector>
#include <algorithm>
#include <ctime>
#include "bvh.h"
#include "vec3.h"
#include "scene.h"
using namespace std;

bvh::bvh(const std::vector<primitive*>& primitives) {
  clock_t time = clock();
  root = recursive_split(primitives, 1);
  time = clock() - time;
  cout << "Time taken to construct BVH of " << primitives.size() << " primitives: " << time << "ms\n";
}

aabb* bvh::get_root() {
	return root;
}

// precondition: primitives is not empty
aabb* bvh::recursive_split(const vector<primitive*> &primitives, unsigned int max_leaf) {
	aabb box;
	aabb centroid_box;


	for (primitive* p: primitives) {
		aabb b = p->get_aabb();
		box.expand(b);
		vec3 centroid = b.centroid();
		centroid_box.expand(centroid);
	}

	aabb* node = new aabb(box);
	if (primitives.size() <= max_leaf) {
		node->primitives = primitives;
		return node;
	} else {
		vec3 dist = centroid_box.max - centroid_box.min;
		double max_dist = max(max(dist.x, dist.y), dist.z);
		int axis;
		double mid_p;

		if (max_dist == dist.x) {
			axis = 0;
		} else if (max_dist == dist.y) {
			axis = 1;
		} else {
			axis = 2;
		}
		vector<primitive*> left, right;
		do {
			left.clear();
			right.clear();
			mid_p = (centroid_box.max[axis] + centroid_box.min[axis])/2;
			for (primitive* p: primitives) {
				if (p->get_aabb().centroid()[axis] > mid_p) {
					right.push_back(p);
				} else {
					left.push_back(p);
				}
			}
			axis = (axis + 1) % 3;
		} while (left.size() == 0 || right.size() == 0);
		node->left = recursive_split(left, max_leaf);
		node->right = recursive_split(right, max_leaf);
		return node;
	}
}

bool bvh::intersect(const ray& r, aabb* node, const primitive *origin) {
	double min = 0;
	double max = DBL_MAX;
	if (node->intersect(r, min, max)) {
		if (node->is_leaf()) {
			for (primitive* p: node->primitives) {
        if (p == origin)
          continue;
				if (p->intersect(r)) {
					return true;
				}
			}
			return false;
		} else {
			return intersect(r, node->left, origin) || intersect(r, node->right, origin);
		}
	} else {
		return false;
	}
}

bool bvh::intersect(const ray& r, aabb* node, intersection *i) {
  double min = 0;
  double max = DBL_MAX;
  if (node->intersect(r, min, max)) {
    if (node->is_leaf()) {
      for (primitive* p : node->primitives) {
        if (p->intersect(r, i)) {
          return true;
        }
      }
      return false;
    } else {
      intersection i1, i2;
      bool r1 = intersect(r, node->left, &i1);
      bool r2 = intersect(r, node->right, &i2);
      if (r1) {
        if (r2 && i1.t > i2.t) {
          *i = i2;
        } else {
          *i = i1;
        }
      } else if (r2) {
        *i = i2;
      } else {
        return false;
      }
      return true;
    }
  }
  return false;
}
