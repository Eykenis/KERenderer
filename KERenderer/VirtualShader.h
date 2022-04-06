#pragma once
#include "geometry.h"
#include "TGA_Image.h"
#include "model.h"
#include "variable.h"

class VirtualShader
{
private:
public:
	Vec3f intensity;
	Model* model = NULL;
	virtual Vec4f vertex(int _face_num, int _nth_vertex) = 0;
	virtual bool fragment(Vec3f bar, TGA_Color& color) = 0;
};