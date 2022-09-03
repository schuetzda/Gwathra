#pragma once
#include "vector3d.h"
#include "matrix3d.h"
namespace gwm {
	struct Quat
	{
		float x, y, z, w;
		Quat() :x(0.f), y(0.f), z(0.f), w(0.f) {}
		Quat(float a[4]) :x(a[0]), y(a[1]), z(a[2]), w(a[3]) {}
		Quat(float a, float b, float c, float d) :x(a), y(b), z(c), w(d) {}
		Quat(Vec3 a, float s) :x(a.v[0]), y(a.v[1]), z(a.v[2]), w(a.v[3]) {}

		const Vec3& getImaginary(void) const;

		Mat3 getRotationMatrix(void);
		void setRotationMatrix(const Mat3& m);
	};
	Quat operator *(const Quat& ql, const Quat& q2);
	Vec3 rotate(const Vec3& v, const Quat& q);

}

