#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include "geometry.h"
#include "macro.h"
#include <cstring>
#include <fstream>

struct TGA_Color;
struct TGA_Header;

class TGA_Image
{
private:
	unsigned char* data;
	int width;
	int height;
	int bytespp;
public:
	enum Format {
		GRAYSCALE = 1,
		RGB = 3,
		RGBA = 4
	};

	TGA_Image(TGA_Image& i) {
		width = i.width;
		height = i.height;
		bytespp = i.bytespp;
		unsigned long nbytes = width * height * bytespp;
		data = new unsigned char[nbytes];
		memcpy(data, i.data, nbytes);
	}
	TGA_Image(int w = WINDOW_WIDTH, int h = WINDOW_HEIGHT, int bpp = 4) {
		width = w, height = h, bytespp = bpp;
		unsigned long nbytes = width * height * bytespp;
		data = new unsigned char[nbytes];
		memset(data, 0, nbytes);
	}
	~TGA_Image() {
		if (data) delete[] data;
 	}
	//void load_TGA(char*);
	//void load_PNG(char*);
	//  void release_TGA_Image();
	bool setColor(int x, int y, TGA_Color c);
	bool load_rle_data(std::ifstream& in);
	bool unload_rle_data(std::ofstream& out);
	TGA_Color get(int x, int y);
	bool read_TGA(const char* filename);
	bool write_TGA(const char* filename, bool rle = 1);
	bool flip_vertically();
	int getWidth() { return width; }
	int getHeight() { return height; }
};
#pragma pack(push, 1)

struct TGA_Header {
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short x_origin;
	short y_origin;
	short width;
	short height;
	char bitsperpixel;
	char imageDescriptor;
};
#pragma pack(pop)

struct TGA_Color {
	union {
		struct {
			unsigned char b, g, r, a;
		};
		unsigned char raw[4];
		unsigned int val;
	};
	int bytespp;

	TGA_Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A = 255) : b(B), g(G), r(R), a(A), bytespp(4) {

	}

	TGA_Color(int v, int bpp) : val(v), bytespp(bpp) {

	}

	TGA_Color(const TGA_Color& c, int bpp) : val(c.val), bytespp(bpp) {

	}

	TGA_Color(const unsigned char* p, int bpp) {
		bytespp = bpp;
		r = p[0];
		g = p[1];
		if (bpp >= 3) b = p[2];
		if (bpp >= 4) a = p[3];
	}

	TGA_Color& operator = (const TGA_Color& c) {
		if (this != &c) {
			bytespp = c.bytespp;
			val = c.val;
		}
		return *this;
	}

	TGA_Color operator * (const float f) {
		return TGA_Color(MIN(255.f, r * f), MIN(255.f, g * f), MIN(255.f, b * f), a);
	}
	TGA_Color operator + (const TGA_Color& o) {
		return TGA_Color(MIN(255.f, r + o.r), MIN(255.f, g + o.g), MIN(255.f, b + o.b), a);
	}
};

#endif // !IMAGE_H

