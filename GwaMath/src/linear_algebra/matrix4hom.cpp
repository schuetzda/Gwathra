#include "matrix4hom.h"

namespace gwm {
	Mat4h::Mat4h() : Mat4{ 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,1.f } {}
	Mat4h::Mat4h(float id) : Mat4{ id } {}
	Mat4h::Mat4h(const Mat3& m, const Vec3& transl) : Mat4{ m.n[0][0], m.n[0][1], m.n[0][2], transl.v[0], m.n[1][0], m.n[1][1], m.n[1][2], transl.v[1], m.n[2][0], m.n[2][1], m.n[2][2], transl.v[2], 0.f, 0.f, 0.f, 1.f} {}
	Mat4h::Mat4h(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23)
		: Mat4{ n00, n01, n02, n03,  n10,n11,n12, n13 ,n20,n21,n22, n23, 0.f, 0.f, 0.f, 1.f } {}

	Mat4h inverse(const Mat4h& h) {
		const Vec3& a = Vec3(h.n[0][0], h.n[0][1], h.n[0][2]);
		const Vec3& b = Vec3(h.n[1][0], h.n[1][1], h.n[1][2]);
		const Vec3& c = Vec3(h.n[2][0], h.n[2][1], h.n[2][2]);
		const Vec3& d = Vec3(h.n[3][0], h.n[3][1], h.n[3][2]);
		Vec3 s = cross(a, b);
		Vec3 t = cross(c, d);

		float invDet = 1.0f / dot(s, c);

		s *= invDet;
		t *= invDet;

		Vec3 v = c * invDet;

		Vec3 r0 = cross(b, v);
		Vec3 r1 = cross(v, a);
		
		return (Mat4h(r0.v[0],  r0.v[1],r0.v[2], -dot(b, t),
					  r1.v[0], r1.v[1] * invDet, r1.v[2], dot(a, t),
					  s.v[0], s.v[1], s.v[2], -dot(d, s)));
	}

	const float determinant(const Mat4h& m)
	{
		return (
			m.n[0][2] * m.n[1][1] * m.n[2][0] + m.n[0][1] * m.n[1][2] * m.n[2][0] +
			m.n[0][2] * m.n[1][0] * m.n[2][1] - m.n[0][0] * m.n[1][2] * m.n[2][1] -
			m.n[0][1] * m.n[1][0] * m.n[2][2] + m.n[0][0] * m.n[1][1] * m.n[2][2]);
	}
	Mat4h operator *(const Mat4h& a, const Mat4h& b) {
		return Mat4h(
			a.n[0][0] * b.n[0][0] + a.n[1][0] * b.n[0][1] + a.n[2][0] * b.n[0][2],
			a.n[0][0] * b.n[1][0] + a.n[1][0] * b.n[1][1] + a.n[2][0] * b.n[1][2],
			a.n[0][0] * b.n[2][0] + a.n[1][0] * b.n[2][1] + a.n[2][0] * b.n[2][2],
			a.n[0][0] * b.n[3][0] + a.n[1][0] * b.n[3][1] + a.n[2][0] * b.n[3][2] + a.n[3][0],
			a.n[0][1] * b.n[0][0] + a.n[1][1] * b.n[0][1] + a.n[2][1] * b.n[0][2],
			a.n[0][1] * b.n[1][0] + a.n[1][1] * b.n[1][1] + a.n[2][1] * b.n[1][2],
			a.n[0][1] * b.n[2][0] + a.n[1][1] * b.n[2][1] + a.n[2][1] * b.n[2][2],
			a.n[0][1] * b.n[3][0] + a.n[1][1] * b.n[3][1] + a.n[2][1] * b.n[3][2] + a.n[3][1],
			a.n[0][2] * b.n[0][0] + a.n[1][2] * b.n[0][1] + a.n[2][2] * b.n[0][2],
			a.n[0][2] * b.n[1][0] + a.n[1][2] * b.n[1][1] + a.n[2][2] * b.n[1][2],
			a.n[0][2] * b.n[2][0] + a.n[1][2] * b.n[2][1] + a.n[2][2] * b.n[2][2],
			a.n[0][2] * b.n[3][0] + a.n[1][2] * b.n[3][1] + a.n[2][2] * b.n[3][2] + a.n[3][2]
		);
	}
	Vec3 operator * (const Mat4h& a, const Vec3& v) {
		return Vec3(
			a.n[0][0] * v.v[0] + a.n[1][0] * v.v[1] + a.n[2][0] * v.v[2],
			a.n[0][1] * v.v[0] + a.n[1][1] * v.v[1] + a.n[2][1] * v.v[2],
			a.n[0][2] * v.v[0] + a.n[1][2] * v.v[1] + a.n[2][2] * v.v[2]);
	}
	Pnt3 operator * (const Mat4h& a, const Pnt3& v) {
		return Pnt3(
			a.n[0][0] * v.v[0] + a.n[1][0] * v.v[1] + a.n[2][0] * v.v[2] + a.n[3][0],
			a.n[0][1] * v.v[0] + a.n[1][1] * v.v[1] + a.n[2][1] * v.v[2] + a.n[3][1],
			a.n[0][2] * v.v[0] + a.n[1][2] * v.v[1] + a.n[2][2] * v.v[2] + a.n[3][2]);
	}
}