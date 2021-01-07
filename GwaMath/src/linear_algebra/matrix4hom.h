#pragma once
#include "matrix4d.h"
#include "matrix3d.h"
#include "vector3d.h"
/*
	Homogenous 4D Matrix with values 0 0 0 1 in the last column
*/
namespace gwm {
	struct Mat4h : Mat4
	{
		Mat4h();
		Mat4h(float id);
		Mat4h(const Mat3& m,const Vec3& transl);
		Mat4h(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23);
	};
	const float determinant(const Mat4h& m);
	Mat4h inverse(const Mat4h& h);
	Mat4h operator *(const Mat4h& a, const Mat4h& b);
	Vec3 operator * (const Mat4h& h, const Vec3& v);
	Pnt3 operator * (const Mat4h& h, const Pnt3& v);
}
