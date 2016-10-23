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
  image_buffer(size_t width = 0, size_t height = 0) :width(width), height(height), data(width * height)  {}

  void set(size_t i, size_t j, rgb color) {
    if (color == vec3{ 0, 0, 0 }) {
      data[j * width + i].r = data[j*width + i].g = data[j*width + i].b = 255;
    } else {
      data[j * width + i].r = static_cast<int>(min(color.x * 256.0, 255.0));
      data[j * width + i].g = static_cast<int>(min(color.y * 256.0, 255.0));
      data[j * width + i].b = static_cast<int>(min(color.z * 256.0, 255.0));
    }
    
  }

  void write_to_png(const char *filename) {
    lodepng::encode(filename, reinterpret_cast<unsigned char*>(&data[0]), width, height, LCT_RGB);
  }

  ~image_buffer() = default;

private:
  struct RGB {
    unsigned char r = 0, g = 0, b = 0;
  };
  size_t width, height;
  vector<RGB> data;
};
#endif
