#ifndef IMAGE_BUFFER
#define IMAGE_BUFFER
#include <memory>
#include "vec3.h"
#include "lodepng.h"
class image_buffer {
public:
  image_buffer(unsigned int width = 0, unsigned int height = 0) :width(width), height(height) {}
  vec3 &operator[] (size_t n) { return data.get()[n]; }
  void write_to_png(char *filename) {
    lodepng::encode(filename, reinterpret_cast<unsigned char *>(data.get()), width, height, LCT_RGB);
  }
  ~image_buffer() = default;

private:
  unsigned int width, height;
  std::unique_ptr<vec3> data;
};
#endif
