#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "geometry.h"
#include "TGA_Image.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class Model{
private:
	std::vector<Vec3f> _verts;
	std::vector<Vec2f> _uvs;
	std::vector<Vec3f> _vns;
	//std::vector<Vec2f> _texcoords;
	std::vector<std::vector<Vec3i>> _faces;
	TGA_Image normal_map;
	TGA_Image diffuse_map;
	TGA_Image specular_map;
public:
	// load .tga image
	void load_normal(const char*);
	void load_diffuse(const char*);
	void load_specular(const char*);

	int nvert() { return _verts.size(); }
	int nface() { return _faces.size(); }

	std::vector<int> face(int i) {
		std::vector<int> ret;
		for (int j = 0; j < (int)_faces[i].size(); ++j) {
			ret.push_back(_faces[i][j].v[0]);
		}
		return ret;
	}
	Vec3f vert(int iface, int nthvert) { 
		return _verts[_faces[iface][nthvert].v[0]];
	}
	Vec3f normal(int iface, int nthvert) {
		return _vns[_faces[iface][nthvert].v[2]];
	}

	Model(const char* filename) : _verts(), _faces(), _vns(), _uvs() {
		std::ifstream in;
		in.open(filename, std::ifstream::in);
		if (in.fail()) return;
		std::string line;
		while (!in.eof()) {
			std::getline(in, line);
			std::istringstream iss(line.c_str());
			char trash;
			if (!line.compare(0, 2, "v ")) {
				iss >> trash;
				Vec3f v;
				for (int i = 0; i < 3; ++i) iss >> v.v[i];
				_verts.push_back(v);
			}
			else if (!line.compare(0, 2, "f ")) {
				iss >> trash;
				Vec3i tmp;
				std::vector<Vec3i> f;
				int cnt = 0;
				while (iss >> tmp.v[0] >> trash >> tmp.v[1] >> trash >> tmp.v[2]) {
					for (int i = 0; i < 3; ++i) {
						tmp.v[i]--;
					}
					f.push_back(tmp);
					cnt++;
				}
				_faces.push_back(f);
			}
			else if (!line.compare(0, 3, "vn ")) {
				iss >> trash >> trash;
				Vec3f n;
				for (int i = 0; i < 3; ++i) iss >> n.v[i];

				_vns.push_back(normalize(n));
			}
			else if (!line.compare(0, 3, "vt ")) {
				iss >> trash >> trash;
				Vec2f uv;
				for (int i = 0; i < 2; ++i) iss >> uv.v[i];
				_uvs.push_back(uv);
			}
		}
		//tex_image = new TGA_Image(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
		std::cout << "#v #" << _verts.size() << " f# " << _faces.size()  << " vn# " << _vns.size() << std::endl;
	}
};


#endif // MODEL_H
