#ifndef IMAGE_BUFFER
#define IMAGE_BUFFER
#include <memory>
#include <vector>
#include <algorithm>
#include "vec3.h"
#include "lodepng.h"
using namespace std;

class image_buffer {
  using size_t = unsigned int;
public:
  image_buffer(size_t width = 0, size_t height = 0) :width(width), height(height), data(width * height) {}

  void set(size_t i, size_t j, rgb color) {
    data[(height - j - 1) * width + i] = color;
  }

  void write_to_png(const char *filename, unsigned int d = 1) {
    vector<size_t> pixels;
    pixels.reserve(width * height);
    
    for (auto i = 0; i < width * height; i++) {
      const rgb &color = data[i];
      size_t compressed = 0;
      compressed += (255 << 24)
         + (static_cast<size_t>(min(color.z * 256.0 / d, 255.0)) << 16)
         + (static_cast<size_t>(min(color.y * 256.0 / d, 255.0)) << 8)
         + static_cast<size_t>(min(color.x * 256.0 / d, 255.0));
       pixels.push_back(compressed);
     }
    lodepng::encode(filename, reinterpret_cast<unsigned char*>(&pixels[0]), width, height, LCT_RGBA);
  }

  ~image_buffer() = default;

private:
  size_t width, height;
  vector<rgb> data;
};
#endif
