#ifndef OBJPARSER
#define OBJPARSER
#include <string>
#include <array>
#include <vector>
#include "triangle.h"
#include "matrix4x4.h"
#include "ellipsoid.h"

class obj_parser {
public:
  obj_parser(std::string filename, vec3 &ka, vec3 &kd, vec4 &ks, vec3 &kr, matrix4x4 &trans) :
    filename(filename), ka(ka), kd(kd), ks(ks), kr(kr), trans(trans) {}
  std::vector<primitive*> parse();
  obj_parser(const obj_parser&) = delete;
  ~obj_parser() = default;

private:
  bool parse_face(std::string &&);
  bool parse_face_index(const char *line, std::vector<unsigned int> &, int &);
 
  std::string filename;
  std::vector<vec3> vertices, normals;
  std::vector<primitive*> primitives;
  vec3 ka, kd, kr;
  vec4 ks;
  matrix4x4 trans;
};

#endif

