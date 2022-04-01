#pragma once
#ifndef DRAW2D_H
#define DRAW2D_H

#include "geometry.h"
#include "TGA_Image.h"

void draw_line(TGA_Image& image, int x_from, int y_from, int x_to, int y_to, TGA_Color color);
void draw_triangle(TGA_Image& image, Vec3f v1, Vec3f v2, Vec3f v3, TGA_Color color);

#endif // !DRAW2D_H
