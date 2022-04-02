#include "pipeline.h"

void rasterizeFrame(TGA_Image& image, Model* model, TGA_Color color) {
	for (int i = 0; i < model->nface(); ++i) {
		std::vector<int> face = model->face(i);
		Vec3f coords[3];
		for (int j = 0; j < 3; ++j) {
			Vec3f v = model->vert(i, j);
			Vec4f vv = Vec4f(v.x, v.y, v.z, 1.0);
			vv.y -= 1.f;
			vv.z -= 2.f;
			vv = get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * vv;
			coords[j] = Vec3f(vv.x / vv.w, vv.y / vv.w, vv.z / vv.w);
		}
		for (int j = 0; j < 3; ++j) {
			draw_line(image, coords[j].x, coords[j].y, coords[(j + 1) % 3].x, coords[(j + 1) % 3].y, color);
		}
	}
}

void rasterizeTri(TGA_Image& image, Model* model, TGA_Color color, VirtualShader& shader, int mode) {
	for (int i = 0; i < model->nface(); ++i) {
			Vec3f screen_coords[3];
			for (int j = 0; j < 3; ++j) {
				Vec4f tmp;
				if (mode == 1) tmp = shader.vertex(i, j);
				else {
					tmp = get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * Vec4f(model->vert(i, j), 1.f);
					tmp.y -= 0.5f;
				}
				screen_coords[j] = Vec3f(tmp.x / tmp.w, tmp.y / tmp.w, tmp.z / tmp.w);
			}
			draw_triangle(image, screen_coords, shader, mode);
	}
}