#pragma once
#ifndef PIPELINE_H
#define PIPELINE_H
#include <cmath>
#include "model.h"
#include "VirtualShader.h"
#include "draw2d.h"

// rasterization (draw)
void rasterizeFrame(TGA_Image& image, Model* model, TGA_Color color);
void rasterizeTri(TGA_Image& image, Model* model, TGA_Color color, VirtualShader& shader, int mode);
#endif // PIPELINE_H
