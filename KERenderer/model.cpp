#include "model.h"

void Model::load_normal(const char* filename) {
	normal_map = new TGA_Image;
	normal_map->read_TGA(filename);
	normal_map->flip_vertically();
}

void Model::load_diffuse(const char* filename) {
	diffuse_map = new TGA_Image;
	diffuse_map->read_TGA(filename);
	diffuse_map->flip_vertically();
}

void Model::load_specular(const char* filename) {
	specular_map = new TGA_Image;
	specular_map->read_TGA(filename);
	specular_map->flip_vertically();
}

TGA_Color Model::diff(float x, float y) {
	x *= diffuse_map->getWidth();
	y *= diffuse_map->getHeight();
	return diffuse_map->get(x, y);
}

TGA_Color Model::norm(float x, float y) {
	x *= normal_map->getWidth();
	y *= normal_map->getHeight();
	return normal_map->get(x, y);
}