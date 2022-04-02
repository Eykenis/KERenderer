#include "geometry.h"
Mat4f* MVP;

// unary operation
float module(Vec3f& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
float module(Vec2f& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}
float module(Vec4f& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vec3f normalize(Vec3f v) {
	float mod = module(v);
	v.x /= mod;
	v.y /= mod;
	v.z /= mod;
	return v;
}
Vec2f normalize(Vec2f v) {
	float mod = module(v);
	v.x /= mod;
	v.y /= mod;
	return v;
}
Vec4f normalize(Vec4f v) {
	float mod = module(v);
	v.x /= mod;
	v.y /= mod;
	v.z /= mod;
	v.w /= mod;
	return v;
}

void setIdentical(Mat3f& m) {
	m.m[0][0] = m.m[1][1] = m.m[2][2] = 1.0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == j) continue;
			m.m[i][j] = 0.0;
		}
	}
}

void setIdentical(Mat4f& m) {
	m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1.0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) continue;
			m.m[i][j] = 0.0;
		}
	}
}
void setIdentical(Mat3i& m) {
	m.m[0][0] = m.m[1][1] = m.m[2][2] = 1;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == j) continue;
			m.m[i][j] = 0;
		}
	}
}
void setIdentical(Mat4i& m) {
	m.m[0][0] = m.m[1][1] = m.m[2][2] = m.m[3][3] = 1;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) continue;
			m.m[i][j] = 0;
		}
	}
}

void setZero(Mat3f& m) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m.m[i][j] = 0.0;
		}
	}
}
void setZero(Mat4f& m) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m.m[i][j] = 0.0;
		}
	}
}
void setZero(Mat3i& m) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m.m[i][j] = 0;
		}
	}
}
void setZero(Mat4i& m) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m.m[i][j] = 0;
		}
	}
}

Vec3f barycentric(Vec2f p, Vec2f a, Vec2f b, Vec2f c) {
	Vec2f v0 = b - a, v1 = c - a, v2 = p - a;
	float d00 = v0 * v0;
	float d01 = v0 * v1;
	float d11 = v1 * v1;
	float d20 = v2 * v0;
	float d21 = v2 * v1;
	float denom = d00 * d11 - d01 * d01;
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	return Vec3f(1.0f - v - w, v, w);
}
bool inTriangle(const Vec3f& bary) {
	return bary.x >= 0 && bary.y >= 0 && bary.z >= 0;
}

Mat4f get_MVP_matrix(float angleX, float angleY, float angleZ) { // Radian degree
	if (MVP) return *MVP;
	Mat4f rot;
	setIdentical(rot);
	rot.m[0][0] = cos(angleY);
	rot.m[0][2] = sin(angleY);
	rot.m[2][0] = -sin(angleY);
	rot.m[2][2] = cos(angleY);

	Mat4f tmp;
	setIdentical(tmp);
	tmp.m[1][1] = cos(angleX);
	tmp.m[2][2] = cos(angleX);
	tmp.m[1][2] = -sin(angleX);
	tmp.m[2][1] = sin(angleX);

	rot = rot * tmp;

	setIdentical(tmp);
	tmp.m[0][0] = cos(angleZ);
	tmp.m[1][1] = cos(angleZ);
	tmp.m[0][1] = -sin(angleZ);
	tmp.m[1][0] = sin(angleZ);

	rot = rot * tmp;

	Mat4f ret;
	setIdentical(ret);
	ret.m[3][2] = -1.f / 4.f;

	Mat4f ortho;
	setIdentical(ortho);
	ortho.m[0][0] = WINDOW_WIDTH / 5.;
	ortho.m[1][1] = WINDOW_HEIGHT / 5.;
	ortho.m[2][2] = WINDOW_DEPTH / 5.;
	ortho.m[0][3] = WINDOW_WIDTH / 10. + WINDOW_WIDTH / 2.f;
	ortho.m[1][3] = WINDOW_HEIGHT / 10. + WINDOW_WIDTH / 4.;
	ortho.m[2][3] = WINDOW_DEPTH / 5.;

	MVP = new Mat4f(ortho * ret * rot);

	return *MVP;
}

void debug_Mat4(Mat4f mat) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << mat.m[i][j] << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}