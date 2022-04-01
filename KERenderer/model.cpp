#include "model.h"

void Model::load_normal(const char* filename) {
	normal_map.read_TGA(filename);
}

void Model::load_diffuse(const char* filename) {
	diffuse_map.read_TGA(filename);
}

void Model::load_specular(const char* filename) {
	specular_map.read_TGA(filename);
}