#include "vector3d.h"
#include "fastcalc.h"
#include <math.h>
namespace gwm
{
	float& Vec3::operator [](const int i) 
	{
		return ((&x)[i]);
	}

	const float& Vec3::operator [](const int i) const
	{
		return ((&x)[i]);
	}

	Vec3& Vec3::operator *=(const float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return (*this);
	}

	Vec3& Vec3::operator/=(const float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return (*this);
	}

	Vec3& Vec3::operator+=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	Vec3& Vec3::operator-=(const Vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}

	const float magnitude(const Vec3& v)
	{
		return  sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	void normalize(Vec3& v) 
	{
		const float mag = v.x * v.x + v.y * v.y + v.z * v.z;
		const float inv_length = fast_rsqrt(mag);
		v.x *= inv_length;
		v.y *= inv_length;
		v.z *= inv_length;
	}

	const float dot(const Vec3& a,const Vec3& b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	const Vec3 cross(const Vec3& a, const Vec3& b)
	{
		return (const Vec3(a.y*b.z - a.z*b.y,
						 a.z*b.x - a.x*b.z, 
						 a.x*b.y - a.y*b.x));
	}

	const Vec3 project(const Vec3& a, const Vec3& b)
	{
		//b * dot(a,b) / dot(b,b)
		float dotAB = a.x*b.x + a.y*b.y + a.z*b.z;
		float dotBB = b.x*b.x + b.y*b.y + b.z*b.z;
		return (const Vec3(b.x*dotAB / dotBB, b.y*dotAB / dotBB, b.z*dotAB / dotBB));
	}

	const Vec3 reject(const Vec3& a, const Vec3& b)
	{
		//a - b * dot(a,b) / dot(b,b)
		float dotAB = a.x*b.x + a.y*b.y + a.z*b.z;
		float dotBB = b.x*b.x + b.y*b.y + b.z*b.z;
		return (const Vec3((a.x-b.x)*dotAB/dotBB,a.y-b.y*dotAB / dotBB,a.z-b.z*dotAB / dotBB));
	}

	Vec3 operator *(Vec3 v, const float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		return v;
	}

	Vec3 operator *(float s, Vec3 v)
	{
		return v * s;
	}

	Vec3 operator /(Vec3 v, float s)
	{
		v.x /= s;
		v.y /= s;
		v.z /= s;
		return v;
	}
	Vec3 operator /(float s, Vec3 v)
	{
		v.x = s / v.x;
		v.y = s / v.y;
		v.z = s / v.z;
		return v;
	}

	Vec3 operator +(const Vec3& a, const Vec3& b)
	{
		return (Vec3(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	Vec3 operator -(const Vec3& a, const Vec3& b)
	{
		return (Vec3(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	Vec3 operator -(const Vec3& a)
	{
		return (Vec3(-a.x,-a.y,-a.z));
	}
}