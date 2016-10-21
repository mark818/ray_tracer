#pragma once
#include <memory>
#include "vec3.h"
#include "lodepng.h"
class image_buffer {
public:
	image_buffer(unsigned int width = 0, unsigned int height = 0) :width(width), height(height) {}
	~image_buffer() = default;
	void write_to_png(char *filename) {
		lodepng::encode(filename, reinterpret_cast<unsigned char *>(data.get()), width, height, LCT_RGB);
	}

private:
	unsigned int width, height;
	std::unique_ptr<vec3> data;
};

