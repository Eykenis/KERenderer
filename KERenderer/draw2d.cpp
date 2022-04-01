#include "draw2d.h"
#include <cmath>
#include <iostream>
float zbuffer[WINDOW_HEIGHT][WINDOW_WIDTH];
bool v[WINDOW_WIDTH][WINDOW_HEIGHT];

void draw_line(TGA_Image& image, int x_from, int y_from, int x_to, int y_to, TGA_Color color) {
	for (float t = 0; t < 1; t += .001) {
		image.setColor(int(x_from + (x_to - x_from) * t), int(y_from + (y_to - y_from) * t), color);
	}
}

void draw_triangle(TGA_Image& image, Vec3f v1, Vec3f v2, Vec3f v3, TGA_Color color) {
	int left_bound_ = std::min(v1.x, std::min(v2.x, v3.x));
	int right_bound_ = std::max(v1.x, std::max(v2.x, v3.x));
	int up_bound_ = std::max(v1.y, std::max(v2.y, v3.y));
	int down_bound_ = std::min(v1.y, std::min(v2.y, v3.y));
	for (int i = left_bound_; i <= right_bound_; i++) {
		for (int j = down_bound_; j <= up_bound_; ++j) {
			if (i <= 0 || j <= 0) continue;
			if (i >= WINDOW_WIDTH || j >= WINDOW_WIDTH) break;
			Vec3f inter = barycentric(Vec3f(i, j, 0), v1, v2, v3);
			float z = inter.x * v1.z + inter.y * v2.z + inter.z * v3.z;
			if (!v[i][j]) {
				zbuffer[i][j] = -1e100;
				v[i][j] = 1;
			}

			if (inTriangle(inter) && z > zbuffer[i][j]) {
				zbuffer[i][j] = z;
				image.setColor(i, j, color);
			}
		}
	}
}