#include <ctime>
#include "platform.h"
#include "geometry.h"
#include "macro.h"
#include "model.h"
#include "TGA_Image.h"
#include "draw2d.h"
#include "pipeline.h"
#include "GouraudShader.h"
#include "PhongShader.h"
#include "FlatShader.h"
#include "BlinnShader.h"
#include "scenes.h"
Scenes scenes;
Model* model;
Vec4f lookat(0.f, 0.f, 1.f, 0.f);
window_t* window = NULL;

float zbuffer[WINDOW_WIDTH][WINDOW_HEIGHT];
void clear_zbuffer();
void clear_frame_buffer(unsigned char* framebuffer);
unsigned char* framebuffer = new unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT * 4];

int main(int argc, char* argv[]) {
	// expected argv: model name, render mode, (tex names)
	// 
	// load model and create image - Initialization
	float prt = platform_get_time();

	const char* string = "./obj/Aiz_v1.0_2.79.obj";
	//const char* string = "./obj/african.obj";

	model = new Model(string, 1);
	model->load_diffuse("./textures/Dungeon_Aiz_diff.tga");
	//model->load_diffuse("./textures/african_head_diffuse.tga");
	memset(framebuffer, 255, sizeof(framebuffer));
	
	float cur = platform_get_time();

	std::cout << "Model " << string << " load successfully. " << "\nTime: " << cur - prt << " seconds." << std::endl;

	BlinnShader shader(model);
	shader.gloss = 15;
	window_init(WINDOW_WIDTH, WINDOW_HEIGHT, L"KERenderer beta 0.2.0");

	lookat = get_rot(ANGLEX, ANGLEY, ANGLEZ) * lookat;

	// update: render model on images
	int	frame_count = 0;
	while (!window->is_close) {
		cur = platform_get_time();
		clear_zbuffer();
		clear_frame_buffer(framebuffer);
		// move and transform
		rasterizeTri(framebuffer, model, WHITE, shader, 1, zbuffer, lookat);
		window_draw(framebuffer);
		msg_dispatch();
		frame_count++;
		if (cur - prt >= 1) {
			std::cout << "FPS: " << frame_count << std::endl;
			prt = platform_get_time();
			frame_count = 0;
		}
	}
	// debug area

	return 0;
}

void clear_zbuffer() {
	for (int i = 0; i < WINDOW_WIDTH; ++i) {
		for (int j = 0; j < WINDOW_HEIGHT; ++j) {
			zbuffer[i][j] = -1e10;
		}
	}
}

void clear_frame_buffer(unsigned char* framebuffer) {
	for (int i = 0; i < WINDOW_HEIGHT; ++i) {
		for (int j = 0; j < WINDOW_WIDTH; ++j) {
			int index = (i * WINDOW_WIDTH + j) * 4;
			framebuffer[index + 2] = 214;
			framebuffer[index + 1] = 233;
			framebuffer[index] = 248;
		}
	}
}