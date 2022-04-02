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
	TGA_Image zbuffer(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	//---------------------------------------------

	std::cout << "Input a number to choose obj files to render, 1 - african head, 2 - A2." << std::endl;
	int x, y;
	std::cin >> x;
	std::cout << "Input a number to choose render mode, 1 - Gouraud shading, 2 - Phong shading, 3 - Z-buffering." << std::endl;
	std::cin >> y;

	if (y == 1) {
		GouraudShader shader(NULL);
		if (x == 1) {
			scenes.african(model, shader, gouraud);
		}
		else if (x == 2) {
			scenes.a2(model, shader, gouraud);
		}
		else {
			std::cerr << "Illegal args" << std::endl;
			return -1;
		}
		gouraud.flip_vertically();
		gouraud.write_TGA("Gouraud.tga");
	}
	else if (y == 2) {
		PhongShader shader(NULL);
		if (x == 1) {
			scenes.african(model, shader, phong);
		}
		else if (x == 2) {
			scenes.a2(model, shader, phong);
		}
		else {
			std::cerr << "Illegal args" << std::endl;
			return -1;
		}
		phong.flip_vertically();
		phong.write_TGA("Phong.tga");
	}
	else if (y == 3) {
		GouraudShader shader(NULL);
		if (x == 1) {
			scenes.african_z(model, shader, zbuffer);
		}
		else if (x == 2) {
			scenes.a2_z(model, shader, zbuffer);
		}
		else {
			std::cerr << "Illegal args" << std::endl;
			return -1;
		}
		zbuffer.flip_vertically();
		zbuffer.write_TGA("Z-Buffer.tga");
	}

	//---------------------------------------------

	return 0;
}