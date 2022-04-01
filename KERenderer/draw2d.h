#pragma once
#ifndef DRAW2D_H
#define DRAW2D_H

#include "geometry.h"
#include "TGA_Image.h"
#include "VirtualShader.h"

void draw_line(TGA_Image& image, int x_from, int y_from, int x_to, int y_to, TGA_Color color);
void draw_triangle(TGA_Image& image, Vec3f* v, VirtualShader& shader);

#endif // !DRAW2D_H
