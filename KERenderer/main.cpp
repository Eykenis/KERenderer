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
#include "variable.h"
#include "mesh.h"

Model* model;
Vec4f lookat(0.f, 0.f, 1.f, 0.f);
window_t* window = NULL;
float zbuffer[WINDOW_WIDTH][WINDOW_HEIGHT];

void clear_zbuffer();
void clear_frame_buffer(unsigned char* framebuffer);
unsigned char* framebuffer = new unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT * 4];

int main(int argc, char* argv[]) {
	// expected argv: model name, render mode, (tex names)

	mesh* mesh_this;
	std::cout << "Enter 1 to render Shoujo Aiz, enter 2 to render african head." << std::endl;
	int x; std::cin >> x;
	if (x == 1) {
		mesh_this = &mesh_Aiz;
	}
	else mesh_this = &mesh_African;

	// load model and create image - Initialization

	float prt = platform_get_time();

	model = new Model(mesh_this->_obj_file_name, 1);
	model->load_diffuse(mesh_this->_dif_file_name);
	memset(framebuffer, 255, sizeof(framebuffer));
	
	float cur = platform_get_time();

	std::cout << "Model " << mesh_this->_obj_file_name << " load successfully. " << "\nTime: " << cur - prt << " seconds." << std::endl;

	BlinnShader bshader(model);
	PhongShader pshader(model);

	window_init(WINDOW_WIDTH, WINDOW_HEIGHT, L"KERenderer beta 0.2.0");

	lookat = get_rot(angleX, angleY, angleZ) * lookat;

	update_MVP_matrix(angleX, angleY, angleZ, scale);

	// update: render model on images
	int	frame_count = 0;
	while (!window->is_close) {
		cur = platform_get_time();
		clear_zbuffer();
		clear_frame_buffer(framebuffer);
		if (x == 1)
		rasterizeTri(framebuffer, model, WHITE, bshader, 1, zbuffer, lookat);
		else rasterizeTri(framebuffer, model, WHITE, pshader, 1, zbuffer, lookat);
		window_draw(framebuffer);
		msg_dispatch();
		frame_count++;

		update_MVP_matrix(angleX, angleY, angleZ, scale);

		if (window->keys[0x25]) { // left
			angleY -= PI/ 60.f;
		}
		else if (window->keys[0x27]) { // right
			angleY += PI / 60.f;
		}
		else if (window->keys[0x26]) { // up
			scale += 0.03f;
		}
		else if (window->keys[0x28]) { // down
			if (scale >= 0.3f) scale -= 0.03f;
		}

		if (cur - prt >= 1) {
			std::cout << "FPS: " << frame_count << std::endl;
			prt = platform_get_time();
			frame_count = 0;
		}
	}

	window_destroy();
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