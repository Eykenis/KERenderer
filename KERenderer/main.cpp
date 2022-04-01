#include <ctime>
#include "geometry.h"
#include "macro.h"
#include "model.h"
#include "TGA_Image.h"
#include "draw2d.h"
#include "pipeline.h"
#include "GouraudShader.h"
#include "scenes.h"
Scenes scenes;
Model* model;
int main(int argc, const char* argv) {
	// argv: model name, render mode, (tex names)

	// load model and create image

	// update: render model on images
	
	// debug area
	clock_t start, end;
	TGA_Image image(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	//rasterizeFrame(image, model, WHITE);
	start = clock();

	//---------------------------------------------
	model = new Model("african.obj");
	GouraudShader shader(model);
	rasterizeTri(image, model, WHITE, shader);

	//scenes.african(model, shader, image);
	

	//---------------------------------------------
	end = clock();
	std::cout << "Used " << (double)(end - start) / CLOCKS_PER_SEC << " secs to draw the diffuse render image.\n";
	image.flip_vertically();
	image.write_TGA("output.tga");
	return 0;
}