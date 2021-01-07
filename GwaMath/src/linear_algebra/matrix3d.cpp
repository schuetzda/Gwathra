#include "matrix3d.h"
namespace gwm {

	Mat3::Mat3() : n{ {0,0,0},{0,0,0},{0,0,0} } {}
	Mat3::Mat3(float id) : n{ {id,0,0},{0,id,0},{0,0,id} } {}
	Mat3::Mat3(float n00, float n01, float n02,
		float n10, float n11, float n12,
		float n20, float n21, float n22) 
		: n{{n00, n10, n20}, { n01,n11,n21 }, { n02,n12,n22 }} {}

	float& Mat3::operator ()(int i, int j)
	{
		return (n[j][i]);
	}
	const float& Mat3::operator ()(int i, int j) const
	{
		return (n[j][i]);
	}

	Mat3& Mat3::operator *=(const float t)
	{
		n[0][0] *= t; n[0][1] *= t; n[0][2] *= t;
		n[0][1] *= t; n[1][1] *= t; n[1][2] *= t;
		n[2][0] *= t; n[2][1] *= t; n[2][2] *= t;
		return (*this);
	}

	Mat3& Mat3::operator /=(const float t)
	{
		n[0][0] /= t; n[0][1] /= t; n[0][2] /= t;
		n[0][1] /= t; n[1][1] /= t; n[1][2] /= t;
		n[2][0] /= t; n[2][1] /= t; n[2][2] /= t;
		return (*this);
	}

	Mat3& Mat3::operator +=(const Mat3& a)
	{
		n[0][0] += a.n[0][0]; n[0][1] += a.n[0][1]; n[0][2] += a.n[0][2];
		n[1][0] += a.n[1][0]; n[1][1] += a.n[1][1]; n[1][2] += a.n[1][2];
		n[2][0] += a.n[2][0]; n[2][1] += a.n[2][1]; n[2][2] += a.n[2][2];
		return (*this);
	}

	Mat3& Mat3::operator -=(const Mat3& a)
	{
		n[0][0] -= a.n[0][0]; n[0][1] -= a.n[0][1]; n[0][2] -= a.n[0][2];
		n[1][0] -= a.n[1][0]; n[1][1] -= a.n[1][1]; n[1][2] -= a.n[1][2];
		n[2][0] -= a.n[2][0]; n[2][1] -= a.n[2][1]; n[2][2] -= a.n[2][2];
		return (*this);
	}


	const float determinant(const Mat3& m)
	{
		return (m.n[0][0] * (m.n[1][1] * m.n[2][2] - m.n[1][2] * m.n[2][1])
			+ m.n[0][1] * (m.n[1][2] * m.n[2][0] - m.n[1][0] * m.n[2][2])
			+ m.n[0][2] * (m.n[1][0] * m.n[2][1] - m.n[1][1] * m.n[2][0]));
	}

	const Mat3 inverse(const Mat3& m)
	{
		const Vec3& a = Vec3(m.n[0][0], m.n[0][1], m.n[0][2]);
		const Vec3& b = Vec3(m.n[1][0], m.n[1][1], m.n[1][2]);
		const Vec3& c = Vec3(m.n[2][0], m.n[2][1], m.n[2][2]);

		Vec3 r0 = cross(b, c);
		Vec3 r1 = cross(c, a);
		Vec3 r2 = cross(a, b);

		float invDet = 1.0f / dot(r2, c);

		return (Mat3(r0.x *invDet, r0.y *invDet, r0.z *invDet,
					r1.x *invDet, r1.y *invDet, r1.z *invDet,
					r2.x *invDet, r2.y *invDet, r2.z *invDet));
	}

	Mat3 operator *(const Mat3& a, const Mat3& b)
	{
		return Mat3(a.n[0][0] * b.n[0][0] + a.n[1][0] * b.n[0][1] + a.n[2][0] * b.n[0][2],
					a.n[0][0] * b.n[1][0] + a.n[1][0] * b.n[1][1] + a.n[2][0] * b.n[1][2],
					a.n[0][0] * b.n[2][0] + a.n[1][0] * b.n[2][1] + a.n[2][0] * b.n[2][2],
					a.n[0][1] * b.n[0][0] + a.n[1][1] * b.n[0][1] + a.n[2][1] * b.n[0][2],
					a.n[0][1] * b.n[1][0] + a.n[1][1] * b.n[1][1] + a.n[2][1] * b.n[1][2],
					a.n[0][1] * b.n[2][0] + a.n[1][1] * b.n[2][1] + a.n[2][1] * b.n[2][2],
					a.n[0][2] * b.n[0][0] + a.n[1][2] * b.n[0][1] + a.n[2][2] * b.n[0][2],
					a.n[0][2] * b.n[1][0] + a.n[1][2] * b.n[1][1] + a.n[2][2] * b.n[1][2],
					a.n[0][2] * b.n[2][0] + a.n[1][2] * b.n[2][1] + a.n[2][2] * b.n[2][2]);
	}

	Vec3 operator *(const Mat3& a, const Vec3& v)
	{
		return Vec3(a.n[0][0] * v.x + a.n[0][1] * v.y + a.n[0][2] * v.z,
					a.n[1][0] * v.x + a.n[1][1] * v.y + a.n[1][2] * v.z,
					a.n[2][0] * v.x + a.n[2][1] * v.y + a.n[2][2] * v.z);
	}

	Mat3 operator +(const Mat3& a, const Mat3& b)
	{
		return Mat3(a.n[0][0] + b.n[0][0], a.n[0][1] + b.n[0][1], a.n[0][2] + b.n[0][2],
					a.n[1][0] + b.n[1][0], a.n[1][1] + b.n[1][1], a.n[1][2] + b.n[1][2],
					a.n[2][0] + b.n[2][0], a.n[2][1] + b.n[2][1], a.n[2][2] + b.n[2][2]);
	}

	Mat3 operator -(const Mat3& a, const Mat3& b)
	{
		return Mat3(a.n[0][0] - b.n[0][0], a.n[0][1] - b.n[0][1], a.n[0][2] - b.n[0][2],
					a.n[1][0] - b.n[1][0], a.n[1][1] - b.n[1][1], a.n[1][2] - b.n[1][2],
					a.n[2][0] - b.n[2][0], a.n[2][1] - b.n[2][1], a.n[2][2] - b.n[2][2]);
	}

	Mat3 operator *(const float t, Mat3 b)
	{
		b.n[0][0] *= t; b.n[0][1] *= t; b.n[0][2] *= t;
		b.n[1][0] *= t; b.n[1][1] *= t; b.n[1][2] *= t;
		b.n[2][0] *= t; b.n[2][1] *= t; b.n[2][2] *= t;
		return b;
	}

	Mat3 operator /(const float t, Mat3 b)
	{
		b.n[0][0] /= t; b.n[0][1] /= t; b.n[0][2] /= t;
		b.n[1][0] /= t; b.n[1][1] /= t; b.n[1][2] /= t;
		b.n[2][0] /= t; b.n[2][1] /= t; b.n[2][2] /= t;
		return b;
	}

}
