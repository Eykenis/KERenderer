#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>
#include <iostream>
#include "macro.h"

template<typename T> struct Vec2
{
	// paras
	union {
		struct {
			T x, y;
		};
		T v[2];
	};

	// constructor
	Vec2<T>() {
		x = y = 0;
	}
	Vec2<T>(T xx, T yy) {
		x = xx;
		y = yy;
	}
	Vec2<T>(const Vec2<T>& v) {
		x = v.x;
		y = v.y;
	}

	// vec-vec calculation
	T operator * (const Vec2<T>& v) {
		return x * v.x + y * v.y;
	}
	Vec2<T> operator + (const Vec2<T>& v) {
		return Vec2<T>(x + v.x, y + v.y);
	}
	Vec2<T> operator - (const Vec2<T>& v) {
		return Vec2<T>(x - v.x, y - v.y);
	}
	Vec2<T> operator * (const T t) {
		return Vec2<T>(x * t, y * t);
	}

	Vec2<T>& operator = (const Vec2<T>& v) {
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
};

template<typename T> struct Vec3
{
	// paras
	union {
		struct {
			T x, y, z;
		};
		T v[3];
	};

	// constructor
	Vec3<T>() {
		x = y = z = 0;
	}
	Vec3<T>(T xx, T yy, T zz) {
		x = xx;
		y = yy;
		z = zz;
	}
	Vec3<T>(const Vec3<T>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	// vec-vec
	T operator * (const Vec3<T>& v) {
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3<T> operator + (const Vec3<T>& v) {
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}
	Vec3<T> operator - (const Vec3<T>& v) {
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}
	Vec3<T> operator * (T t) {
		return Vec3<T>(x * t, y * t, z * t);
	}
	Vec3<T> operator ^ (const Vec3<T>& v) {
		return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	Vec3<T>& operator = (const Vec3<T>& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	}
};

template<typename T> struct Vec4
{
	union {
		struct {
			T x, y, z, w;
		};
		T v[4];
	};

	// constructor
	Vec4<T>() {
		x = y = z = w = 0;
	}
	Vec4<T>(T xx, T yy, T zz, T ww) {
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}
	Vec4<T>(const Vec4<T>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	Vec4<T>(const Vec3<T>& v, T t) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = t;
	}
	
	// vec-vec
	T operator * (const Vec4<T>& v) {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}
	Vec4<T> operator + (const Vec4<T>& v) {
		return Vec4<T>(x + v.x, y + v.y, z + y.z, w + v.w);
	}
	Vec4<T> operator - (const Vec4<T>& v) {
		return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	Vec4<T> operator * (const T t) {
		return Vec4<T>(x * t, y * t, z * t, w * t);
	}
};

template<typename T> struct Mat3
{
	T m[3][3];

	// constructor
	Mat3<T>() {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				m[i][j] = 0;
			}
		}
	}
	Mat3<T>(T t[3][3]) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				m[i][j] = t[i][j];
			}
		}
	}
	Mat3<T>(Mat3<T>& t) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				m[i][j] = t.m[i][j];
			}
		}
	}

	// mat-mat
	Mat3<T> operator + (const Mat3<T>& t) {
		Mat3<T> mat;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				mat[i][j] = this->m[i][j] + t.m[i][j];
			}
		}
		return mat;
	}
	Mat3<T> operator - (const Mat3<T>& t) {
		Mat3<T> mat;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				mat[i][j] = this->m[i][j] - t.m[i][j];
			}
		}
		return mat;
	}
	Mat3<T> operator * (const Mat3<T>& t) {
		Mat3<T> mat;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				mat.m[i][j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j];
			}
		}
		return mat;
	}
	Mat3<T> operator * (const T t) {
		Mat3<T> mat;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				mat.m[i][j] = this->m[i][j] * t;
			}
		}
		return mat;
	}
	Vec3<T> operator * (const Vec3<T>& t) {
		Vec3<T> vec;
		for (int i = 0; i < 4; ++i) {
			vec.v[i] = m[i][0] * t.v[0] + m[i][1] * t.v[1] + m[i][2] * t.v[2];
		}
		return vec;
	}

	T det() {
		return	m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] -
				m[2][0] * m[1][1] * m[0][2] - m[2][1] * m[1][2] * m[0][0] - m[2][2] * m[1][0] * m[0][1];
	}
};

// for homogeous coordinates
template<typename T> struct Mat4
{
	// paras
	T m[4][4];

	// constructor
	Mat4<T>() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m[i][j] = 0;
			}
		}
	}
	Mat4<T>(const T t[4][4]) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m[i][j] = t[i][j];
			}
		}
	}
	Mat4<T>(const Mat4<T>& t) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m[i][j] = t.m[i][j];
			}
		}
	}

	// mat-mat
	Mat4<T> operator + (const Mat4<T>& t) {
		Mat4<T> mat;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				mat[i][j] = this->m[i][j] + t.m[i][j];
			}
		}
		return mat;
	}
	Mat4<T> operator - (const Mat4<T>& t) {
		Mat4<T> mat;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				mat[i][j] = this->m[i][j] - t.m[i][j];
			}
		}
		return mat;
	}
	Mat4<T> operator * (const Mat4<T>& t) {
		Mat4<T> mat;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				mat.m[i][j] = m[i][0] * t.m[0][j] + m[i][1] * t.m[1][j] + m[i][2] * t.m[2][j] + m[i][3] * t.m[3][j];
			}
		}
		return mat;
	}
	Mat4<T> operator * (const T t) {
		Mat4<T> mat;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				mat.m[i][j] = this->m[i][j] * t;
			}
		}
		return mat;
	}
	Vec4<T> operator * (const Vec4<T>& t) {
		Vec4<T> vec;
		for (int i = 0; i < 4; ++i) {
			vec.v[i] = m[i][0] * t.v[0] + m[i][1] * t.v[1] + m[i][2] * t.v[2] + m[i][3] * t.v[3];
		}
		return vec;
	}

	Mat3<T> minor(int row, int col) {
		Mat3<T> ret;
		for (int i = 2; i >= 0; --i) {
			for (int j = 2; j >= 0; --j) {
				ret.m[i][j] = m[i < row ? i : i + 1][j < col ? j : j + 1];
			}
		}
		return ret;
	}

	Mat4<T> adjugate() {
		Mat4<T> ret;
		setZero(ret);
		for (int i = 3; i >= 0; --i) {
			for (int j = 3; j >= 0; --j) {
				ret.m[i][j] = (minor(i, j).det()) * ((i + j) % 2 ? -1 : 1);
			}
		}
		return ret;
	}

	Mat4<T> inverse_transpose() {
		Mat4<T> ret = adjugate();
		T tmp = ret.m[0][0] * m[0][0] + ret.m[0][1] * m[0][1] + ret.m[0][2] * m[0][2];
		return ret * (1.f / tmp);
	}
};

#define Vec2i Vec2<int>
#define Vec2f Vec2<float>
#define Vec3i Vec3<int>
#define Vec3f Vec3<float>
#define Vec4f Vec4<float>
#define Vec4i Vec4<int>
#define Mat3i Mat3<int>
#define Mat3f Mat3<float>
#define Mat4f Mat4<float>
#define Mat4i Mat4<int>

// unary operation
float module(Vec2f&);
float module(Vec3f&);
float module(Vec4f&);
Vec2f normalize(Vec2f);
Vec3f normalize(Vec3f);
Vec4f normalize(Vec4f);
void setIdentical(Mat3f&);
void setIdentical(Mat4f&);
void setIdentical(Mat3i&);
void setIdentical(Mat4i&);
void setZero(Mat3f&);
void setZero(Mat4f&);
void setZero(Mat3i&);
void setZero(Mat4i&);

Vec3f barycentric(Vec2f p, Vec2f a, Vec2f b, Vec2f c);
bool inTriangle(const Vec3f&); // use barycentric's ret value
Mat4f get_MVP_matrix(float angleX, float angleY, float angleZ);
void debug_Mat4(Mat4f);

#endif // GEOMETRY_H