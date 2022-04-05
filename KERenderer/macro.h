#pragma once
#ifndef MACRO_H
#define MACRO_H

#define PI acos(-1.0)
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define MODEL_WIDTH 400
#define MODEL_HEIGHT 400
#define MODEL_DEPTH 1

#define WHITE TGA_Color(255, 255, 255, 255)
#define RED TGA_Color(255, 0, 0, 255)

#define FOVY  (PI / 3.f)
#define ASPECT (WINDOW_WIDTH / WINDOW_HEIGHT)
#define ANGLEX (0.f)
#define ANGLEY (-PI / 6.f)
#define ANGLEZ (0.f)
#define LIGHT_DIR Vec3f(0.f, 0.3f, 1.f)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#endif // !MACRO_H
