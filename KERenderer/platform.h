#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#pragma once
#include <Windows.h>

typedef struct mouse {

}mouse_t;

typedef struct window {
	HWND h_window;
	HDC mem_dc;
	HBITMAP bm_old;
	HBITMAP bm_dib;
	unsigned char* window_fb;
	int width;
	int height;
	char keys[512];
	char buttons[2];
	int is_close;
	mouse_t mouse_info;
}window_t;

extern window_t* window;

int window_init(int width, int height, LPCWSTR title);
int window_destroy();
void window_draw(unsigned char* framebuffer);
void msg_dispatch();
float platform_get_time(void);

#endif // PLATFORM_H