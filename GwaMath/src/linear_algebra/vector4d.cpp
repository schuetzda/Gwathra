#include "vector4d.h"
#include <math.h>
#include "fastcalc.h"

namespace gwm
{
	float& Vec4::operator [](const int i)
	{
		return v[i];
	}

	const float& Vec4::operator [](const int i) const
	{
		return v[i];
	}

	Vec4& Vec4::operator *=(const float s)
	{
		v[0] *= s;
		v[1] *= s;
		v[2] *= s;
		v[3] *= s;
		return (*this);
	}

	Vec4& Vec4::operator/=(const float s)
	{
		v[0] /= s;
		v[1] /= s;
		v[2] /= s;
		v[3] /= s;
		return (*this);
	}

	Vec4& Vec4::operator+=(const Vec4& x)
	{
		v[0] += x.v[0];
		v[1] += x.v[1];
		v[2] += x.v[2];
		v[3] += x.v[3];
		return (*this);
	}

	Vec4& Vec4::operator-=(const Vec4& x)
	{
		v[0] -= x.v[0];
		v[1] -= x.v[1];
		v[2] -= x.v[2];
		v[3] -= x.v[3];
		return (*this);
	}

	Vec4::Vec4(const Vec3& x)
	{
		v[0] = x.v[0];
		v[1] = x.v[1];
		v[2] = x.v[2];
		v[3] = 1.f;
	}

	Vec4::Vec4(const Pnt3& a)
	{
		v[0] = a.v[0];
		v[1] = a.v[1];
		v[2] = a.v[2];
		v[3] = 0.f;
	}

	Vec4::operator Vec3()
	{
		return Vec3(v[0], v[1], v[2]);
	}

	const float magnitude(const Vec4& x)
	{
		return  sqrtf(x.v[0] * x.v[0] + x.v[1] * x.v[1] + x.v[2] * x.v[2] + x.v[3] * x.v[3]);
	}

	void normalize(Vec4& v)
	{
		const float mag = v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
		const float inv_length = fast_rsqrt(mag);
		v.v[0] *= inv_length;
		v.v[1] *= inv_length;
		v.v[2] *= inv_length;
		v.v[3] *= inv_length;
	}

	const float dot(const Vec4& a, const Vec4& b)
	{
		return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3];
	}

	const Vec4 project(const Vec4& a, const Vec4& b)
	{
		//b * dot(a,b) / dot(b,b)
		float dotAB = a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3];
		float dotBB = b.v[0] * b.v[0] + b.v[1] * b.v[1] + b.v[2] * b.v[2] + b.v[3] * b.v[3];
		return (const Vec4(b.v[0] * dotAB / dotBB, b.v[1] * dotAB / dotBB, b.v[2] * dotAB / dotBB, b.v[3] * dotAB / dotBB));
	}

	const Vec4 reject(const Vec4& a, const Vec4& b)
	{
		//a - b * dot(a,b) / dot(b,b)
		float dotAB = a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2] + a.v[3] * b.v[3];
		float dotBB = b.v[0] * b.v[0] + b.v[1] * b.v[1] + b.v[2] * b.v[2] + b.v[3] * b.v[3];
		return (const Vec4((a.v[0] - b.v[0]) * dotAB / dotBB, a.v[1] - b.v[1] * dotAB / dotBB, a.v[2] - b.v[2] * dotAB / dotBB, a.v[3] - b.v[3] * dotAB / dotBB));
	}

	Vec4 operator *(Vec4 v, const float s)
	{
		v.v[0] *= s;
		v.v[1] *= s;
		v.v[2] *= s;
		v.v[3] *= s;
		return v;
	}

	Vec4 operator *(float s, Vec4 v)
	{
		return v * s;
	}

	Vec4 operator /(Vec4 v, float s)
	{
		v.v[0] /= s;
		v.v[1] /= s;
		v.v[2] /= s;
		v.v[3] /= s;
		return v;
	}
	Vec4 operator /(float s, Vec4 v)
	{
		v.v[0] = s / v.v[0];
		v.v[1] = s / v.v[1];
		v.v[2] = s / v.v[2];
		v.v[3] = s / v.v[3];
		return v;
	}

	Vec4 operator +(const Vec4& a, const Vec4& b)
	{
		return (Vec4(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2], a.v[3] + b.v[3]));
	}

	Vec4 operator -(const Vec4& a, const Vec4& b)
	{
		return (Vec4(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2], a.v[3] + b.v[3]));
	}

	Vec4 operator -(const Vec4& a)
	{
		return (Vec4(-a.v[0], -a.v[1], -a.v[2], -a.v[3]));
	}
}