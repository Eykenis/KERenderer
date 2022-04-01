#include <iostream>
#include <fstream>
#include "TGA_Image.h"

bool TGA_Image::write_TGA(const char* filename, bool rle) {
	unsigned char developer_area_ref[4] = { 0, 0, 0, 0 };
	unsigned char extension_area_ref[4] = { 0, 0, 0, 0 };
	unsigned char footer[18] = {'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I', 'O', 'N', '-', 'X', 'F', 'I', 'L', 'E', '.', '\0'};
	
	std::ofstream out;
	out.open(filename, std::ios::binary);
	if (!out.is_open()) {
		std::cerr << "cannot open file " << filename << "\n";
		out.close();
		return false;
	}
	TGA_Header header;
	memset((void*)&header, 0, sizeof(header));
	header.bitsperpixel = bytespp << 3;
	header.width = width;
	header.height = height;
	header.dataTypeCode = (bytespp == GRAYSCALE ? (rle ? 11 : 3) : (rle ? 10 : 2));
	header.imageDescriptor = 0x20;

	out.write((char*)&header, sizeof(header));

	if (!out.good()) {
		std::cerr << "dump failed" << "\n";
		out.close();
		return false;
	}
	if (!rle) {
		out.write((char*)data, width * height * bytespp);
		if (!out.good()) {
			std::cerr << "can't unload raw data" << "\n";
			out.close();
			return false;
		}
	}
	else {
		if (!unload_rle_data(out)) {
			out.close();
			std::cerr << "unload failed\n";
			return false;
		}
	}

	out.write((char*)developer_area_ref, sizeof(developer_area_ref));
	if (!out.good()) {
		std::cerr << "dump failed" << "\n";
		out.close();
		return false;
	}
	out.write((char*)extension_area_ref, sizeof(extension_area_ref));
	if (!out.good()) {
		std::cerr << "dump failed" << "\n";
		out.close();
		return false;
	}
	out.write((char*)footer, sizeof(footer));
	if (!out.good()) {
		std::cerr << "dump failed" << "\n";
		out.close();
		return false;
	}
	out.close();
	return true;
}

bool TGA_Image::setColor(int x, int y, TGA_Color c) {
	if (!data || x < 0 || y < 0 || x >= width || y >= height) {
		return false;
	}
	memcpy(data + (x + y * width) * bytespp, c.raw, bytespp);
	return true;
}

TGA_Color TGA_Image::get(int x, int y) {
	if (!data || x < 0 || y < 0 || x >= width || y >= height) {
		return TGA_Color(0, 0, 0, 255); // Black
	}
	return TGA_Color(data + (x + y * width) * bytespp, bytespp);
}

bool TGA_Image::unload_rle_data(std::ofstream& out) {
	const unsigned char max_chunk_length = 128;
	unsigned long npixels = width * height;
	unsigned long curpix = 0;
	while (curpix < npixels) {
		unsigned long chunkstart = curpix * bytespp;
		unsigned long curbyte = curpix * bytespp;
		unsigned char run_length = 1;
		bool raw = 1;
		while (curpix + run_length < npixels && run_length < max_chunk_length) {
			bool succ_eq = 1;
			for (int t = 0; succ_eq && t < bytespp; ++t) {
				succ_eq = (data[curbyte + t] == data[curbyte + t + bytespp]);
			}
			curbyte += bytespp;
			if (1 == run_length) {
				raw = !succ_eq;
			}
			if (raw && succ_eq) {
				run_length--;
				break;
			}
			if (!raw && !succ_eq) {
				break;
			}
			run_length++;
		}
		curpix += run_length;
		out.put(raw ? run_length - 1 : run_length + 127);
		if (!out.good()) {
			std::cerr << "dump failed\n";
			return false;
		}
		out.write((char*)(data + chunkstart), (raw ? run_length * bytespp : bytespp));
		if (!out.good()) {
			std::cerr << "dump failed\n";
			return false;
		}
	}
	return true;
}

bool TGA_Image::flip_vertically() {
	if (!data) return false;
	unsigned long bytes_per_line = width * bytespp;
	unsigned char* line = new unsigned char[bytes_per_line];
	int half = height >> 1;
	for (int j = 0; j < half; ++j) {
		unsigned long l1 = j * bytes_per_line;
		unsigned long l2 = (height - 1 - j) * bytes_per_line;
		memmove((void*)line, (void*)(data + l1), bytes_per_line);
		memmove((void*)(data + l1), (void*)(data + l2), bytes_per_line);
		memmove((void*)(data + l2), (void*)line, bytes_per_line);
	} delete[] line;
	return true;
}