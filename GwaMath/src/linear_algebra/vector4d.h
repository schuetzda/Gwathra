#pragma once
#include "vector3d.h"
#include "point3d.h"

namespace gwm
{
	struct Vec4
	{
		float v[4];

		Vec4() :v{ 0.f,0.f,0.f,0.f } {}
		Vec4(const float x, const float y, const float z, const float w) : v{ x,y,z,w } {}

		float& operator [](const int i);
		const float& operator [](const int i) const;
		Vec4& operator*=(const float s);
		Vec4& operator/=(const float s);
		Vec4& operator+=(const Vec4& x);
		Vec4& operator-=(const Vec4& x);
		Vec4(const Vec3& x);
		Vec4(const Pnt3& a);
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
