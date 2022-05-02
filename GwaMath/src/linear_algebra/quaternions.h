#pragma once
#include "vector3d.h"
#include "matrix3d.h"
namespace gwm {
	struct Quaternion
	{
		float x, y, z, w;
		Quaternion() :x(0.f), y(0.f), z(0.f), w(0.f) {}
		Quaternion(float a[4]) :x(a[0]), y(a[1]), z(a[2]), w(a[3]) {}
		Quaternion(float a, float b, float c, float d) :x(a), y(b), z(c), w(d) {}
		Quaternion(Vec3 a, float s) :x(a.v[0]), y(a.v[1]), z(a.v[2]), w(a.v[3]) {}

		const Vec3& getImaginary(void) const;

		Mat3 getRotationMatrix(void);
		void setRotationMatrix(const Mat3& m);
	};
	Quaternion operator *(const Quaternion& ql, const Quaternion& q2);
	Vec3 rotate(const Vec3& v, const Quaternion& q);

}

