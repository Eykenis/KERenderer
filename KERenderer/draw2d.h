#pragma once
#ifndef DRAW2D_H
#define DRAW2D_H

#include "geometry.h"
#include "TGA_Image.h"
#include "VirtualShader.h"

void draw_line(TGA_Image& image, int x_from, int y_from, int x_to, int y_to, TGA_Color color);
void draw_triangle(unsigned char* framebuffer, Vec3f* v, VirtualShader& shader, int mode, float zbuffer[][WINDOW_HEIGHT]);
void draw_pixel(unsigned char* framebuffer, int x, int y, TGA_Color color);

#endif // !DRAW2D_H
