#include <ctime>
#include "geometry.h"
#include "macro.h"
#include "model.h"
#include "TGA_Image.h"
#include "draw2d.h"
#include "pipeline.h"
#include "GouraudShader.h"
#include "PhongShader.h"
#include "scenes.h"
Scenes scenes;
Model* model;
int main(int argc, const char* argv) {
	// argv: model name, render mode, (tex names)

	// load model and create image

	// update: render model on images
	
	// debug area
	clock_t start, end;
	TGA_Image phong(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	TGA_Image gouraud(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	TGA_Image zbuffer(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	//rasterizeFrame(image, model, WHITE);

	//---------------------------------------------
	GouraudShader gshader(NULL);

	scenes.a2(model, gshader, zbuffer);

	PhongShader pshader(NULL);

	scenes.a2(model, pshader, zbuffer);

	//---------------------------------------------
	phong.flip_vertically();
	phong.write_TGA("phong.tga");
	gouraud.flip_vertically();
	gouraud.write_TGA("gouraud.tga");
	return 0;
}