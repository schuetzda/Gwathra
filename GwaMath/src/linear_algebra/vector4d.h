#pragma once
#include "vector3d.h"
#include "point3d.h"

namespace gwm
{
	struct Vec4
	{
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 0.f;

		Vec4() : x(0), y(0), z(0), w(0) {}
		Vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z),w(w) {}

		float& operator [](const int i);
		const float& operator [](const int i) const;
		Vec4& operator*=(const float s);
		Vec4& operator/=(const float s);
		Vec4& operator+=(const Vec4& v);
		Vec4& operator-=(const Vec4& v);
		Vec4(const Vec3& v);
		Vec4(const Pnt3& v);
		explicit operator Vec3();
	};

	const float magnitude(const Vec4& v);
	void normalize(Vec4& v);
	const float dot(const Vec4& a, const Vec4& b);
	const Vec4 project(const Vec4& a, const Vec4& b);
	const Vec4 reject(const Vec4& a, const Vec4& b);

	Vec4 operator *(Vec4 v, float s);
	Vec4 operator *(float s, Vec4 v);
	Vec4 operator /(Vec4 v, float s);
	Vec4 operator /(float s, Vec4 v);
	Vec4 operator +(const Vec4& a, const Vec4& b);
	Vec4 operator -(const Vec4& a, const Vec4& b);
	Vec4 operator -(const Vec4& a);
}
