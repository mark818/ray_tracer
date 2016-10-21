#pragma once
#include "vec3.h"
struct light {
	bool isPoint;
	vec3 xyz;
	double r, g, b;
};