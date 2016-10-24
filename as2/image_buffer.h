#ifndef IMAGE_BUFFER
#define IMAGE_BUFFER
#include <memory>
#include <vector>
#include <algorithm>
#include "vec3.h"
#include "lodepng.h"
using namespace std;

class image_buffer {
  typedef unsigned int size_t;
public:
  image_buffer(size_t width = 0, size_t height = 0) :width(width), height(height), data(width * height, 0)  {}

  void set(size_t i, size_t j, rgb color) {
    size_t compressed = 0;
    if (color.z > 0) { 
      printf("get pixel's color: %zu %zu: %f %f %f\n", i, j, min(color.x * 256.0, 255.0), min(color.y * 256.0, 255.0), min(color.z * 256.0, 255.0));
    }
    if (i== 400 || j == 400) {
      data[j * width + i] = static_cast<size_t>(-1);
    } else {
    compressed += (255 << 24)
               +  (static_cast<size_t>(min(color.z * 256.0, 255.0)) << 16)
               +  (static_cast<size_t>(min(color.y * 256.0, 255.0)) << 8)
               +   static_cast<size_t>(min(color.x * 256.0, 255.0));
    data[j * width + i] = compressed;  
    }
    
  }

  void write_to_png(const char *filename) {
    lodepng::encode(filename, reinterpret_cast<unsigned char*>(&data[0]), width, height, LCT_RGBA);
  }

  ~image_buffer() = default;

private:
  size_t width, height;
  vector<size_t> data;
};
#endif
