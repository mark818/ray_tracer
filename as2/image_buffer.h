#ifndef IMAGE_BUFFER
#define IMAGE_BUFFER
#include <memory>
#include <algorithm>
#include "vec3.h"
#include "lodepng.h"
using namespace std;

class image_buffer {
 // typedef unsigned int size_t;
public:
  image_buffer(unsigned int width = 0, unsigned int height = 0) :width(width), height(height) {}

  void set(unsigned int i, unsigned int j, rgb color) {
    unsigned int compressed = 0;
    compressed += static_cast<unsigned int>(min(color.x * 256.0, 255.0)) << 16
                        + static_cast<unsigned int>(min(color.y * 256.0, 255.0)) << 8
                        + static_cast<unsigned int>(min(color.z * 256.0, 255.0));
    data.get()[j * width + i] = compressed;
  }

  void write_to_png(const char *filename) {
    lodepng::encode(filename, reinterpret_cast<unsigned char*>(data.get()), width, height, LCT_RGB);
  }

  ~image_buffer() = default;

private:
  unsigned int width, height;
  std::unique_ptr<unsigned int> data;
};
#endif
