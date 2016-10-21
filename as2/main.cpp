#include <sstream>
#include <iostream>
#include <vector>
#include "ray_tracer.h"
using namespace std;

vec3 ka, kd, ks;
double sp, spu, spv;
bool isSp = false;
vector<light> lights;

double is_valid_double(char *str) {
	static stringstream ss;
	ss.clear();
	ss << str;
	double res;
	ss >> res;
	if (!ss.fail())
		return res;
	return -FLT_MAX;
}

void set_ka(double r, double g, double b) {
	ka = { r, g, b };
}

void set_kd(double r, double g, double b) {
	kd = { r, g, b };
}

void set_ks(double r, double g, double b) {
	ks = { r, g, b };
}

void set_spu(double val) {
	spu = val;
}

void set_spv(double val) {
	spv = val;
}

void set_sp(double val) {
	sp = val;
}

void set_pl(double x, double y, double z, double r, double g, double b) {
	lights.push_back({ true, vec3{ x, y, z }, r, g, b });
}

void set_dl(double x, double y, double z, double r, double g, double b) {
	lights.push_back({ false, vec3{ x, y, z }, r, g, b });
}


inline bool is_within(double val, double max, double min = 0) {
	return val >= min && val <= max;
}

inline void quit_with_error() {
	cerr << "Invalid arguments.\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	char *filename = nullptr;
	for (int i = 1; i < argc;) {
		if (strcmp(argv[i], "-ka") == 0 && (i + 3 < argc)) {
			double r = is_valid_double(argv[i + 1]);
			double g = is_valid_double(argv[i + 2]);
			double b = is_valid_double(argv[i + 3]);
			if (is_within(r, 1) && is_within(g, 1) && is_within(b, 1)) {
				set_ka(r, g, b);
				i += 4;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-kd") == 0 && (i + 3 < argc)) {
			double r = is_valid_double(argv[i + 1]);
			double g = is_valid_double(argv[i + 2]);
			double b = is_valid_double(argv[i + 3]);
			if (is_within(r, 1) && is_within(g, 1) && is_within(b, 1)) {
				set_kd(r, g, b);
				i += 4;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-ks") == 0 && (i + 3 < argc)) {
			double r = is_valid_double(argv[i + 1]);
			double g = is_valid_double(argv[i + 2]);
			double b = is_valid_double(argv[i + 3]);
			if (is_within(r, 1) && is_within(g, 1) && is_within(b, 1)) {
				set_ks(r, g, b);
				i += 4;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-spu") == 0 && (i + 1 < argc)) {
			double val = is_valid_double(argv[i + 1]);
			if (is_within(val, FLT_MAX)) {
				set_spu(val);
				i += 2;
				isSp = false;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-spv") == 0 && (i + 1 < argc)) {
			double val = is_valid_double(argv[i + 1]);
			if (is_within(val, FLT_MAX)) {
				set_spv(val);
				i += 2;
				isSp = false;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-sp") == 0 && (i + 1 < argc)) {
			double val = is_valid_double(argv[i + 1]);
			if (is_within(val, FLT_MAX)) {
				set_sp(val);
				i += 2;
				isSp = true;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-pl") == 0 && (i + 6 < argc)) {
			double x = is_valid_double(argv[i + 1]);
			double y = is_valid_double(argv[i + 2]);
			double z = is_valid_double(argv[i + 3]);
			double r = is_valid_double(argv[i + 4]);
			double g = is_valid_double(argv[i + 5]);
			double b = is_valid_double(argv[i + 6]);
			if (x > -FLT_MAX && y > -FLT_MAX && z > -FLT_MAX &&
				is_within(r, FLT_MAX) && is_within(g, FLT_MAX) && is_within(b, FLT_MAX)) {
				set_pl(x, y, z, r, g, b);
				i += 7;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-dl") == 0 && (i + 6 < argc)) {
			double x = is_valid_double(argv[i + 1]);
			double y = is_valid_double(argv[i + 2]);
			double z = is_valid_double(argv[i + 3]);
			double r = is_valid_double(argv[i + 4]);
			double g = is_valid_double(argv[i + 5]);
			double b = is_valid_double(argv[i + 6]);
			if (x > -FLT_MAX && y > -FLT_MAX && z > -FLT_MAX &&
				is_within(r, FLT_MAX) && is_within(g, FLT_MAX) && is_within(b, FLT_MAX)) {
				set_dl(x, y, z, r, g, b);
				i += 7;
			}
			else
				quit_with_error();
		}
		else if (strcmp(argv[i], "-o") == 0 && (i + 1 < argc)) {
			filename = argv[i + 1];
			i += 2;
		}
		else
			quit_with_error();
	}
}