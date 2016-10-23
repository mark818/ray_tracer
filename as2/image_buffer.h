#ifndef IMAGE_BUFFER
#define IMAGE_BUFFER
#include <memory>
#include <vector>
#include <algorithm>
#include "vec3.h"
#include "lodepng.h"
using namespace std;

class image_buffer {
  typedef size_t size_t;
public:
  image_buffer(size_t width = 0, size_t height = 0) :width(width), height(height), data(width * height, 0)  {}

  void set(size_t i, size_t j, rgb color) {
    size_t compressed = 0;
    compressed += (static_cast<size_t>(min(color.x * 256.0, 255.0)) << 16)
               +  (static_cast<size_t>(min(color.y * 256.0, 255.0)) << 8)
               +   static_cast<size_t>(min(color.z * 256.0, 255.0));
    data[j * width + i] = compressed;
  }

  void write_to_png(const char *filename) {
    lodepng::encode(filename, reinterpret_cast<unsigned char*>(&data[0]), width, height, LCT_RGB);
  }

  ~image_buffer() = default;

private:
  size_t width, height;
  vector<size_t> data;
};
#endif
