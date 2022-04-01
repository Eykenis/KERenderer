#include "draw2d.h"
#include <cmath>
#include <iostream>
double zbuffer[WINDOW_WIDTH][WINDOW_HEIGHT];
bool vis[WINDOW_WIDTH][WINDOW_HEIGHT];

void draw_line(TGA_Image& image, int x_from, int y_from, int x_to, int y_to, TGA_Color color) {
	for (float t = 0; t < 1; t += .001) {
		image.setColor(int(x_from + (x_to - x_from) * t), int(y_from + (y_to - y_from) * t), color);
	}
}

void draw_triangle(TGA_Image& image, Vec3f* v, VirtualShader& shader) {
	int left_bound_ = std::min(v[0].x, std::min(v[1].x, v[2].x));
	int right_bound_ = std::max(v[0].x, std::max(v[1].x, v[2].x));
	int up_bound_ = std::max(v[0].y, std::max(v[1].y, v[2].y));
	int down_bound_ = std::min(v[0].y, std::min(v[1].y, v[2].y));
	Vec2i P;
	for (P.x = left_bound_; P.x <= right_bound_; ++P.x) {
		for (P.y = down_bound_; P.y <= up_bound_; ++P.y) {
			if (P.y <= 0 || P.y >= WINDOW_HEIGHT || P.x <= 0 || P.x >= WINDOW_WIDTH) continue;
			Vec3f interpolate = barycentric(Vec2f(P.x, P.y), Vec2f(v[0].x, v[0].y), Vec2f(v[1].x, v[1].y), Vec2f(v[2].x, v[2].y));
			float z = interpolate.x * v[0].z + interpolate.y * v[1].z + interpolate.z * v[2].z;

			TGA_Color color(255, 255, 255, 255);

			if (!vis[P.x][P.y]) {
				vis[P.x][P.y] = 1;
				zbuffer[P.x][P.y] = -1e10;
			}

			if (inTriangle(interpolate) && z > zbuffer[P.x][P.y]) {
				if (!shader.fragment(interpolate, color)) {
					// vertex shader only
					zbuffer[P.x][P.y] = z;
					//image.setColor(P.x, P.y, TGA_Color(255, 255, 255) * std::min(z * 2.f, 1.f)); // ZBuffering
					image.setColor(P.x, P.y, color); // Gouraud/Phong
				}
			}
		}
	}
}