#include "vector4d.h"
#include <math.h>

namespace gwm
{
	float& Vec4::operator [](const int i)
	{
		return ((&x)[i]);
	}

	const float& Vec4::operator [](const int i) const
	{
		return ((&x)[i]);
	}

	Vec4& Vec4::operator *=(const float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return (*this);
	}

	Vec4& Vec4::operator/=(const float s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return (*this);
	}

	Vec4& Vec4::operator+=(const Vec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return (*this);
	}

	Vec4& Vec4::operator-=(const Vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return (*this);
	}

	Vec4::Vec4(const Vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1.f;
	}

	Vec4::Vec4(const Pnt3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0.f;
	}

	Vec4::operator Vec3()
	{
		return Vec3(x, y, z);
	}

	const float magnitude(const Vec4& v)
	{
		return  sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	}

	void normalize(Vec4& v)
	{
		float mag = magnitude(v);
		v.x /= mag;
		v.y /= mag;
		v.z /= mag;
		v.w /= mag;
	}

	const float dot(const Vec4& a, const Vec4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	const Vec4 project(const Vec4& a, const Vec4& b)
	{
		//b * dot(a,b) / dot(b,b)
		float dotAB = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		float dotBB = b.x * b.x + b.y * b.y + b.z * b.z + b.w * b.w;
		return (const Vec4(b.x * dotAB / dotBB, b.y * dotAB / dotBB, b.z * dotAB / dotBB, b.w * dotAB / dotBB));
	}

	const Vec4 reject(const Vec4& a, const Vec4& b)
	{
		//a - b * dot(a,b) / dot(b,b)
		float dotAB = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		float dotBB = b.x * b.x + b.y * b.y + b.z * b.z + b.w * b.w;
		return (const Vec4((a.x - b.x) * dotAB / dotBB, a.y - b.y * dotAB / dotBB, a.z - b.z * dotAB / dotBB, a.w - b.w * dotAB / dotBB));
	}

	Vec4 operator *(Vec4 v, const float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		v.w *= s;
		return v;
	}

	Vec4 operator *(float s, Vec4 v)
	{
		return v * s;
	}

	Vec4 operator /(Vec4 v, float s)
	{
		v.x /= s;
		v.y /= s;
		v.z /= s;
		v.w /= s;
		return v;
	}
	Vec4 operator /(float s, Vec4 v)
	{
		v.x = s / v.x;
		v.y = s / v.y;
		v.z = s / v.z;
		v.w = s / v.w;
		return v;
	}

	Vec4 operator +(const Vec4& a, const Vec4& b)
	{
		return (Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
	}

	Vec4 operator -(const Vec4& a, const Vec4& b)
	{
		return (Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w + b.w));
	}

	Vec4 operator -(const Vec4& a)
	{
		return (Vec4(-a.x, -a.y, -a.z, -a.w));
	}
}