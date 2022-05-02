#include "vector3d.h"
#include "fastcalc.h"
#include <math.h>
namespace gwm
{
	float& Vec3::operator [](const int i) 
	{
		return v[i];
	}

	const float& Vec3::operator [](const int i) const
	{
		return v[i];
	}

	Vec3& Vec3::operator *=(const float s)
	{
		v[0] *= s;
		v[1] *= s;
		v[2] *= s;
		return (*this);
	}

	Vec3& Vec3::operator/=(const float s)
	{
		v[0] /= s;
		v[1] /= s;
		v[2] /= s;
		return (*this);
	}

	Vec3& Vec3::operator+=(const Vec3& x)
	{
		v[0] += x.v[0];
		v[1] += x.v[1];
		v[2] += x.v[2];
		return (*this);
	}

	Vec3& Vec3::operator-=(const Vec3& x)
	{
		v[0] -= x.v[0];
		v[1] -= x.v[1];
		v[2] -= x.v[2];
		return (*this);
	}

	float* Vec3::getVec()
	{
		return (&v[0]);
	}

	const float magnitude(const Vec3& v)
	{
		return  sqrtf(v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2]);
	}

	void normalize(Vec3& v) 
	{
		const float mag = v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
		const float inv_length = fast_rsqrt(mag);
		v.v[0] *= inv_length;
		v.v[1] *= inv_length;
		v.v[2] *= inv_length;
	}

	const float dot(const Vec3& a,const Vec3& b)
	{
		return a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2];
	}

	const Vec3 cross(const Vec3& a, const Vec3& b)
	{
		return (const Vec3(a.v[1]*b.v[2] - a.v[2]*b.v[1],
						 a.v[2]*b.v[0] - a.v[0]*b.v[2], 
						 a.v[0]*b.v[1] - a.v[1]*b.v[0]));
	}

	const Vec3 project(const Vec3& a, const Vec3& b)
	{
		//b * dot(a,b) / dot(b,b)
		float dotAB = a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2];
		float dotBB = b.v[0]*b.v[0] + b.v[1]*b.v[1] + b.v[2]*b.v[2];
		return (const Vec3(b.v[0]*dotAB / dotBB, b.v[1]*dotAB / dotBB, b.v[2]*dotAB / dotBB));
	}

	const Vec3 reject(const Vec3& a, const Vec3& b)
	{
		//a - b * dot(a,b) / dot(b,b)
		float dotAB = a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2];
		float dotBB = b.v[0]*b.v[0] + b.v[1]*b.v[1] + b.v[2]*b.v[2];
		return (const Vec3((a.v[0]-b.v[0])*dotAB/dotBB,a.v[1]-b.v[1]*dotAB / dotBB,a.v[2]-b.v[2]*dotAB / dotBB));
	}

	Vec3 operator *(Vec3 v, const float s)
	{
		v.v[0] *= s;
		v.v[1] *= s;
		v.v[2] *= s;
		return v;
	}

	Vec3 operator *(float s, Vec3 v)
	{
		return v * s;
	}

	Vec3 operator /(Vec3 v, float s)
	{
		v.v[0] /= s;
		v.v[1] /= s;
		v.v[2] /= s;
		return v;
	}
	Vec3 operator /(float s, Vec3 v)
	{
		v.v[0] = s / v.v[0];
		v.v[1] = s / v.v[1];
		v.v[2] = s / v.v[2];
		return v;
	}

	Vec3 operator +(const Vec3& a, const Vec3& b)
	{
		return (Vec3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]));
	}

	Vec3 operator -(const Vec3& a, const Vec3& b)
	{
		return (Vec3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]));
	}

	Vec3 operator -(const Vec3& a)
	{
		return (Vec3(-a.v[0],-a.v[1],-a.v[2]));
	}
}