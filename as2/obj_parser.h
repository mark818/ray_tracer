#ifndef OBJPARSER
#define OBJPARSER
#include <string>
#include <array>
#include <vector>
#include "triangle.h"
#include "ellipsoid.h"

class obj_parser {
public:
  obj_parser(std::string filename) :filename(filename) {}
  std::vector<primitive*> parse();
  obj_parser(const obj_parser&) = delete;
  ~obj_parser() = default;

private:
  std::array<char *, 4> string_split_4(char buf[], char delim = ' ');
  bool parse_face(std::array<char *, 4> &line, unsigned int vert[], unsigned int norm[], size_t vert_len, size_t norm_len);
  std::string filename;
};

#endif

