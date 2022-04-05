#pragma once
#ifndef PIPELINE_H
#define PIPELINE_H
#include <cmath>
#include "model.h"
#include "VirtualShader.h"
#include "draw2d.h"

// rasterization (draw)
void rasterizeFrame(TGA_Image& image, Model* model, TGA_Color color);
void rasterizeTri(unsigned char* framebuffer, Model* model, TGA_Color color, VirtualShader& shader, int mode, float zbuffer[][WINDOW_HEIGHT], Vec4f lookat);
#endif // PIPELINE_H
