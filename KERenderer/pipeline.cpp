#include "pipeline.h"
Vec3f light_dir(-0.5, 0.2, -1);

void rasterizeTex(TGA_Image& image, Model* model, TGA_Color color) {

}

void rasterizeFrame(TGA_Image& image, Model* model, TGA_Color color) {
	for (int i = 0; i < model->nface(); ++i) {
		std::vector<int> face = model->face(i);
		Vec3f coords[3];
		for (int j = 0; j < 3; ++j) {
			Vec3f v = model->vert(face[j]);
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

void rasterizeTri(TGA_Image& image, Model* model, TGA_Color color) {
	for (int i = 0; i < model->nface(); ++i) {
		std::vector<int> face = model->face(i);
			Vec3f screen_coords[3];
			Vec3f world_coords[3];
			for (int j = 0; j < 3; ++j) {
				Vec3f v = model->vert(face[j]);
				Vec4f vv = Vec4f(v.x, v.y, v.z, 1.0);
				//vv.y -= 1.f;
				vv = get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * vv;
				screen_coords[j] = Vec3f(vv.x / vv.w, vv.y / vv.w, vv.z / vv.w);
				world_coords[j] = v;
			}
			Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
			normalize(n);
			normalize(light_dir);
			float intensity = n * light_dir;
			float ambient = 30.f;
			if (intensity > 0) {
				draw_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], TGA_Color(std::min(255.f, color.r * intensity + ambient), std::min(255.f, color.g * intensity + ambient), std::min(255.f, color.b * intensity + ambient), 255));
			}
			else draw_triangle(image, screen_coords[0], screen_coords[1], screen_coords[2], TGA_Color(ambient, ambient, ambient, 255));
	}
}