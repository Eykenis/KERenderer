#include <ctime>
#include "geometry.h"
#include "macro.h"
#include "model.h"
#include "TGA_Image.h"
#include "draw2d.h"
#include "pipeline.h"
#pragma g++ optimize(3)

Model* model;
int main(int argc, const char* argv) {
	// argv: model name, render mode, (tex names)

	// load model and create image

	// update: render model on images
	
	// debug area
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	clock_t start, end;
	start = clock();
	model = new Model("african.obj");
	end = clock();
	std::cout << "Used " << (double)(end - start) / CLOCKS_PER_SEC << " secs to load .obj model.\n";
	TGA_Image image(WINDOW_WIDTH, WINDOW_HEIGHT, TGA_Image::RGB);
	//rasterizeFrame(image, model, WHITE);
	start = clock();
	rasterizeTri(image, model, TGA_Color(255, 255, 255, 255));
	end = clock();
	std::cout << "Used " << (double)(end - start) / CLOCKS_PER_SEC << " secs to draw the diffuse render image.\n";
	image.flip_vertically();
	image.write_TGA("output.tga");
	return 0;
}