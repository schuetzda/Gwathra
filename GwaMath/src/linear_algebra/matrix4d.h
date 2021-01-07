#pragma once
#include "vector4d.h"
#include "matrix3d.h"
namespace gwm {
	struct Mat4 {
		float n[4][4];

		Mat4();
		Mat4(float id);
		Mat4(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23,
			float n30, float n31, float n32, float n33);

		float& operator ()(int i, int j);
		const float& operator ()(int i, int j) const;
		Mat4& operator *=(const float t);
		Mat4& operator /=(const float t);
		Mat4& operator +=(const Mat4& a);
		Mat4& operator -=(const Mat4& a);
		explicit Mat4(const Mat3& m);
		explicit operator Mat3();
	};

	//Calculates determinant using the Leibnitz formula
	const float determinant(const Mat4& m);
	const Mat4 inverse(const Mat4& m);

	Mat4 operator *(const Mat4& a, const Mat4& b);
	Vec4 operator *(const Mat4& a, const Vec4& v);
	Mat4 operator +(const Mat4& a, const Mat4& b);
	Mat4 operator -(const Mat4& a, const Mat4& b);
	Mat4 operator *(const float t, Mat4 b);
	Mat4 operator *(const float t, Mat4 b);
	Mat4 operator /(const float t, Mat4 b);
	Mat4 operator /(const float t, Mat4 b);
}

