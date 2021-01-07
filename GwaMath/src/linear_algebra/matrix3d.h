#pragma once
#include "vector3d.h"

namespace gwm {
	struct Mat3 {
		float n[3][3];

		Mat3();
		Mat3(float id);
		Mat3(float n00, float n01, float n02,
			float n10, float n11, float n12,
			float n20, float n21, float n22);

		float& operator ()(int i, int j);
		const float& operator ()(int i, int j) const;
		Mat3& operator *=(const float t);
		Mat3& operator /=(const float t);
		Mat3& operator +=(const Mat3& a);
		Mat3& operator -=(const Mat3& a);
	};

	//Calculates determinant using the Leibnitz formula
	const float determinant(const Mat3& m);
	const Mat3 inverse(const Mat3& m);

	Mat3 operator *(const Mat3& a, const Mat3& b);
	Vec3 operator *(const Mat3& a, const Vec3& v);
	Mat3 operator +(const Mat3& a, const Mat3& b);
	Mat3 operator -(const Mat3& a, const Mat3& b);
	Mat3 operator *(const float t, Mat3 b);
	Mat3 operator /(const float t, Mat3 b);
}
