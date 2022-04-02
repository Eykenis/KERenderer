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
int main(int argc, char* argv[]) {
	// argv: model name, render mode, (tex names)

	// load model and create image

	// update: render model on images
	
	// debug area
	clock_t start, end;
	TGA_Image phong(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	TGA_Image gouraud(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	GouraudShader gshader(NULL);
	PhongShader pshader(NULL);
	//---------------------------------------------

	if (argc == 0) {
		scenes.a2(model, gshader, gouraud);
		scenes.a2(model, pshader, phong);
	}
	else if (argv[0] == "1") {
		scenes.a2(model, gshader, gouraud);
		scenes.a2(model, pshader, phong);
	}
	else if (argv[0] == "2") {
		scenes.african(model, gshader, gouraud);
		scenes.african(model, pshader, phong);
	}

	//---------------------------------------------
	phong.flip_vertically();
	phong.write_TGA("phong.tga");
	gouraud.flip_vertically();
	gouraud.write_TGA("gouraud.tga");
	return 0;
}