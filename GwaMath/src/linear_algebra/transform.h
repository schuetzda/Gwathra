#pragma once
#include "matrix3d.h"
#include "matrix4d.h"
#include "matrix4hom.h"
#include "vector3d.h"

namespace gwm {
	Mat3 getRotMatrix3X(float angle);
	Mat3 getRotMatrix3Y(float angle);
	Mat3 getRotMatrix3Z(float angle);
	Mat3 getRotMatrix3(float angle, Vec3 axis);
	Mat4h getRotMatrix4X(float angle);
	Mat4h getRotMatrix4Y(float angle);
	Mat4h getRotMatrix4Z(float angle);
	Mat4h getRotMatrix4(float angle, Vec3 axis);

	Mat3 getScaleMatrix3(float sx, float sy, float sz);
	Mat3 getScaleMatrix3(float s, const Vec3& v);
	Mat4h getScaleMatrix4(float sx, float sy, float sz);
	Mat4h getScaleMatrix4(float s, const Vec3& v);

	void translate(Mat4& m, Vec3 transl);
	void setTranslation(Mat4& m, Vec3 transl);

	void transpose(Mat4& m);

	Mat4 getProjectionMat(float fovY, float aspectRatio, float znear, float zfar);
}