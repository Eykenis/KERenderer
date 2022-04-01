#pragma once
#ifndef PIPELINE_H
#define PIPELINE_H
#include <cmath>
#include "model.h"
#include "VirtualShader.h"
#include "draw2d.h"

// get matrix


// projection & z-buffering


// rasterization (draw)
void rasterizeTex(TGA_Image& image, Model* model, TGA_Color color);
void rasterizeFrame(TGA_Image& image, Model* model, TGA_Color color);
void rasterizeTri(TGA_Image& image, Model* model, TGA_Color color, VirtualShader shader);
#endif // PIPELINE_H
