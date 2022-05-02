#include "matrix4d.h"
namespace gwm {

	Mat4::Mat4() : n{ {0.f,0.f,0.f,0.f},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f,0.f},{0.f,0.f,0.f,0.f} } {}
	Mat4::Mat4(float id) : n{ {id,0.f,0.f,0.f},{0.f,id,0.f,0.f},{0.f,0.f,id,0.f}, {0.f,0.f,0.f,1.f} } {}
	Mat4::Mat4(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23,
		float n30, float n31, float n32, float n33)
		: n{ {n00, n10, n20, n30}, { n01,n11,n21, n31 }, { n02,n12,n22, n32 }, { n03,n13,n23, n33 } } {}

	float& Mat4::operator ()(int i, int j)
	{
		return (n[j][i]);
	}
	const float& Mat4::operator ()(int i, int j) const
	{
		return (n[j][i]);
	}

	Mat4& Mat4::operator *=(const float t)
	{
		n[0][0] *= t; n[0][1] *= t; n[0][2] *= t; n[0][3] *= t;
		n[1][0] *= t; n[1][1] *= t; n[1][2] *= t; n[1][3] *= t;
		n[2][0] *= t; n[2][1] *= t; n[2][2] *= t; n[2][3] *= t;
		n[3][0] *= t; n[3][1] *= t; n[3][2] *= t; n[3][3] *= t;
		return (*this);
	}

	Mat4& Mat4::operator /=(const float t)
	{
		n[0][0] /= t; n[0][1] /= t; n[0][2] /= t; n[0][3] /= t;
		n[1][0] /= t; n[1][1] /= t; n[1][2] /= t; n[1][3] /= t;
		n[2][0] /= t; n[2][1] /= t; n[2][2] /= t; n[2][3] /= t;
		n[3][0] /= t; n[3][1] /= t; n[3][2] /= t; n[3][3] /= t;
		return (*this);
	}

	Mat4& Mat4::operator +=(const Mat4& a)
	{
		n[0][0] += a.n[0][0]; n[0][1] += a.n[0][1]; n[0][2] += a.n[0][2]; n[0][3] += a.n[0][3];
		n[1][0] += a.n[1][0]; n[1][1] += a.n[1][1]; n[1][2] += a.n[1][2]; n[1][3] += a.n[1][3];
		n[2][0] += a.n[2][0]; n[2][1] += a.n[2][1]; n[2][2] += a.n[2][2]; n[2][3] += a.n[2][3];
		n[3][0] += a.n[3][0]; n[3][1] += a.n[3][1]; n[3][2] += a.n[3][2]; n[3][3] += a.n[3][3];
		return (*this);
	}

	Mat4& Mat4::operator -=(const Mat4& a)
	{
		n[0][0] -= a.n[0][0]; n[0][1] -= a.n[0][1]; n[0][2] -= a.n[0][2]; n[0][3] -= a.n[0][3];
		n[1][0] -= a.n[1][0]; n[1][1] -= a.n[1][1]; n[1][2] -= a.n[1][2]; n[1][3] -= a.n[1][3];
		n[2][0] -= a.n[2][0]; n[2][1] -= a.n[2][1]; n[2][2] -= a.n[2][2]; n[2][3] -= a.n[2][3];
		n[3][0] -= a.n[2][0]; n[3][1] -= a.n[3][1]; n[3][2] -= a.n[3][2]; n[3][3] -= a.n[3][3];
		return (*this);
	}

	Mat4::Mat4(const Mat3& m)
	{
		n[0][0] = m.n[0][0]; n[0][1] = m.n[0][1]; n[0][2] = m.n[0][2];
		n[1][0] = m.n[1][0]; n[1][1] = m.n[1][1]; n[1][2] = m.n[1][2];
		n[2][0] = m.n[2][0]; n[2][1] = m.n[2][1]; n[2][2] = m.n[2][2];
		n[3][0] = 0.f; n[3][1] = 0.f; n[3][2] = 0.f;
		n[0][3] = 0.f; n[1][3] = 0.f; n[2][3] = 0.f; n[3][3] = 1.f;
	}

	Mat4::operator Mat3()
	{
		return Mat3(n[0][0], n[0][1], n[0][2],
					n[1][0], n[1][1], n[1][2],
					n[2][0], n[2][1], n[2][2]);
	}


	const float determinant(const Mat4& m)
	{
		float det2x2_1 = m.n[2][2] * m.n[3][3] - m.n[3][2] * m.n[2][3];
		float det2x2_2 = m.n[2][1] * m.n[3][3] - m.n[3][1] * m.n[2][3];
		float det2x2_3 = m.n[2][1] * m.n[3][2] - m.n[3][1] * m.n[2][2];
		float det2x2_4 = m.n[2][0] * m.n[3][3] - m.n[3][0] * m.n[2][3];
		float det2x2_5 = m.n[2][0] * m.n[3][2] - m.n[3][0] * m.n[2][2];
		float det2x2_6 = m.n[2][0] * m.n[3][1] - m.n[3][0] * m.n[2][1];

		float det3x3_1 = m.n[1][1] * det2x2_1 - m.n[1][2] * det2x2_2 + m.n[1][3] * det2x2_3;
		float det3x3_2 = -(m.n[1][0] * det2x2_1 - m.n[1][2] * det2x2_4 + m.n[1][3] * det2x2_5);
		float det3x3_3 = m.n[1][0] * det2x2_2 - m.n[1][1] * det2x2_4 + m.n[1][3] * det2x2_6;
		float det3x3_4 = -(m.n[1][0] * det2x2_3 - m.n[1][1] * det2x2_5 + m.n[1][2] * det2x2_6);

		return m.n[0][0] * det3x3_1 + m.n[0][1] * det3x3_2 + m.n[0][2] * det3x3_3 + m.n[0][3] * det3x3_4;
	}

	const Mat4 inverse(const Mat4& m)
	{
		const Vec3& a = Vec3(m.n[0][0], m.n[0][1], m.n[0][2]);
		const Vec3& b = Vec3(m.n[1][0], m.n[1][1], m.n[1][2]);
		const Vec3& c = Vec3(m.n[2][0], m.n[2][1], m.n[2][2]);
		const Vec3& d = Vec3(m.n[3][0], m.n[3][1], m.n[3][2]);

		Vec3 s = cross(a, b);
		Vec3 t = cross(c, d);
		Vec3 u = a * m.n[1][3] - b * m.n[0][3];
		Vec3 v = c * m.n[3][3] - d * m.n[2][3];

		float invDet = 1.0f / (dot(s, v) + dot(t,u));

		s *= invDet;
		t *= invDet;
		u *= invDet;
		v *= invDet;

		Vec3 r0 = cross(b, v) + t * m.n[1][3];
		Vec3 r1 = cross(v, a) - t * m.n[0][3];
		Vec3 r2 = cross(d, u) + s * m.n[3][3];
		Vec3 r3 = cross(u, c) - s * m.n[2][3];

		return (Mat4(
			r0.v[0], r0.v[1], r0.v[2], -dot(b, t),
			r1.v[0], r1.v[1], r1.v[2], dot(a, t),
			r2.v[0], r2.v[1], r2.v[2], -dot(d, s),
			r3.v[0], r3.v[1], r3.v[2], dot(c, s)));
	}

	Mat4 operator *(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			a.n[0][0] * b.n[0][0] + a.n[1][0] * b.n[0][1] + a.n[2][0] * b.n[0][2] + a.n[3][0] * b.n[0][3],
			a.n[0][0] * b.n[1][0] + a.n[1][0] * b.n[1][1] + a.n[2][0] * b.n[1][2] + a.n[3][0] * b.n[1][3],
			a.n[0][0] * b.n[2][0] + a.n[1][0] * b.n[2][1] + a.n[2][0] * b.n[2][2] + a.n[3][0] * b.n[2][3],
			a.n[0][0] * b.n[3][0] + a.n[1][0] * b.n[3][1] + a.n[2][0] * b.n[3][2] + a.n[3][0] * b.n[3][3],
			a.n[0][1] * b.n[0][0] + a.n[1][1] * b.n[0][1] + a.n[2][1] * b.n[0][2] + a.n[3][1] * b.n[0][3],
			a.n[0][1] * b.n[1][0] + a.n[1][1] * b.n[1][1] + a.n[2][1] * b.n[1][2] + a.n[3][1] * b.n[1][3],
			a.n[0][1] * b.n[2][0] + a.n[1][1] * b.n[2][1] + a.n[2][1] * b.n[2][2] + a.n[3][1] * b.n[2][3],
			a.n[0][1] * b.n[3][0] + a.n[1][1] * b.n[3][1] + a.n[2][1] * b.n[3][2] + a.n[3][1] * b.n[3][3],
			a.n[0][2] * b.n[0][0] + a.n[1][2] * b.n[0][1] + a.n[2][2] * b.n[0][2] + a.n[3][2] * b.n[0][3],
			a.n[0][2] * b.n[1][0] + a.n[1][2] * b.n[1][1] + a.n[2][2] * b.n[1][2] + a.n[3][2] * b.n[1][3],
			a.n[0][2] * b.n[2][0] + a.n[1][2] * b.n[2][1] + a.n[2][2] * b.n[2][2] + a.n[3][2] * b.n[2][3],
			a.n[0][2] * b.n[3][0] + a.n[1][2] * b.n[3][1] + a.n[2][2] * b.n[3][2] + a.n[3][2] * b.n[3][3],
			a.n[0][3] * b.n[0][0] + a.n[1][3] * b.n[0][1] + a.n[2][3] * b.n[0][2] + a.n[3][3] * b.n[0][3],
			a.n[0][3] * b.n[1][0] + a.n[1][3] * b.n[1][1] + a.n[2][3] * b.n[1][2] + a.n[3][3] * b.n[1][3],
			a.n[0][3] * b.n[2][0] + a.n[1][3] * b.n[2][1] + a.n[2][3] * b.n[2][2] + a.n[3][3] * b.n[2][3],
			a.n[0][3] * b.n[3][0] + a.n[1][3] * b.n[3][1] + a.n[2][3] * b.n[3][2] + a.n[3][3] * b.n[3][3]
		);
	}

	Vec4 operator *(const Mat4& a, const Vec4& v)
	{
		return Vec4(
			a.n[0][0] * v.v[0] + a.n[1][0] * v.v[1] + a.n[2][0] * v.v[2] + a.n[3][0] * v.v[3],
			a.n[0][1] * v.v[0] + a.n[1][1] * v.v[1] + a.n[2][1] * v.v[2] + a.n[3][1] * v.v[3],
			a.n[0][2] * v.v[0] + a.n[1][2] * v.v[1] + a.n[2][2] * v.v[2] + a.n[3][2] * v.v[3],
			a.n[0][3] * v.v[0] + a.n[1][3] * v.v[1] + a.n[2][3] * v.v[2] + a.n[3][3] * v.v[3]);
	}

	Mat4 operator +(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			a.n[0][0] + b.n[0][0], a.n[0][1] + b.n[0][1], a.n[0][2] + b.n[0][2], a.n[0][3] + b.n[0][3],
			a.n[1][0] + b.n[1][0], a.n[1][1] + b.n[1][1], a.n[1][2] + b.n[1][2], a.n[1][3] + b.n[1][3],
			a.n[2][0] + b.n[2][0], a.n[2][1] + b.n[2][1], a.n[2][2] + b.n[2][2], a.n[2][3] + b.n[2][3], 
			a.n[3][0] + b.n[3][0], a.n[3][1] + b.n[3][1], a.n[3][2] + b.n[3][2], a.n[3][3] + b.n[3][3]);
	}

	Mat4 operator -(const Mat4& a, const Mat4& b)
	{
		return Mat4(
			a.n[0][0] - b.n[0][0], a.n[0][1] - b.n[0][1], a.n[0][2] - b.n[0][2], a.n[0][3] - b.n[0][3],
			a.n[1][0] - b.n[1][0], a.n[1][1] - b.n[1][1], a.n[1][2] - b.n[1][2], a.n[1][3] - b.n[1][3],
			a.n[2][0] - b.n[2][0], a.n[2][1] - b.n[2][1], a.n[2][2] - b.n[2][2], a.n[2][3] - b.n[2][3],
			a.n[3][0] - b.n[3][0], a.n[3][1] - b.n[3][1], a.n[3][2] - b.n[3][2], a.n[3][3] - b.n[3][3]);
	}

	Mat4 operator *(const float t, Mat4 b)
	{
		b.n[0][0] *= t; b.n[0][1] *= t; b.n[0][2] *= t; b.n[0][3] *= t;
		b.n[1][0] *= t; b.n[1][1] *= t; b.n[1][2] *= t; b.n[1][3] *= t;
		b.n[2][0] *= t; b.n[2][1] *= t; b.n[2][2] *= t; b.n[2][3] *= t;
		b.n[3][0] *= t; b.n[3][1] *= t; b.n[3][2] *= t; b.n[3][3] *= t;
		return b;
	}

	Mat4 operator /(const float t, Mat4 b)
	{
		b.n[0][0] /= t; b.n[0][1] /= t; b.n[0][2] /= t; b.n[0][3] /= t;
		b.n[1][0] /= t; b.n[1][1] /= t; b.n[1][2] /= t; b.n[1][3] /= t;
		b.n[2][0] /= t; b.n[2][1] /= t; b.n[2][2] /= t; b.n[2][3] /= t;
		b.n[3][0] /= t; b.n[3][1] /= t; b.n[3][2] /= t; b.n[3][3] /= t;
		return b;
	}

}
