#include "transform.h"
#include "matrix3d.h"
#include "matrix4d.h"
#include <cmath>
namespace gwm {
	Mat3 getRotMatrix3X(float angle) {
		return Mat3(1.f, 0.f, 0.f,
					0.f, cos(angle), -sin(angle),
					0.f, sin(angle), cos(angle));
	}
	Mat3 getRotMatrix3Y(float angle) {
		return Mat3(cos(angle), 0.f, sin(angle),
					0.f, 1.f, 0.f,
					-sin(angle), 0.f, cos(angle));
	}
	Mat3 getRotMatrix3Z(float angle) {
		return Mat3(cos(angle), -sin(angle), 0.f,
					sin(angle), cos(angle), 0.f,
					0.f, 0.f, 1.f);
	}

	Mat3 getRotMatrix3(float angle, Vec3 axis)
	{
		float c = cos(angle);
		float s = sin(angle);
		float d = 1.f - c;

		return Mat3(c + d * axis.v[0] * axis.v[0], d * axis.v[0] * axis.v[1] - s * axis.v[2], d * axis.v[0] * axis.v[2] + s * axis.v[1],
					d * axis.v[0] * axis.v[1] + s * axis.v[2], c + d * axis.v[1] * axis.v[1], d * axis.v[1] * axis.v[2] - s * axis.v[0],
					d * axis.v[0] * axis.v[2] - s * axis.v[1], d * axis.v[1] * axis.v[2] + s * axis.v[0], c + d * axis.v[2] * axis.v[2]);
	}

	Mat4h getRotMatrix4X(float angle) {
		return Mat4h(1.f, 0.f, 0.f, 0.f,
					0.f, cos(angle), -sin(angle), 0.f,
					0.f, sin(angle), cos(angle), 0.f);
	}
	Mat4h getRotMatrix4Y(float angle) {
		return Mat4h(cos(angle), 0.f, sin(angle), 0.f,
					0.f, 1.f, 0.f, 0.f,
					-sin(angle), 0.f, cos(angle), 0.f);
	}
	Mat4h getRotMatrix4Z(float angle) {
		return Mat4h(cos(angle), -sin(angle), 0.f, 0.f,
						sin(angle), cos(angle), 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f);
	}

	Mat4h getRotMatrix4(float angle, Vec3 axis) {
		normalize(axis);

		float c = cos(angle);
		float s = sin(angle);
		float d = 1.f - c;

		return Mat4h(c + d * axis.v[0] * axis.v[0], d * axis.v[0] * axis.v[1] - s * axis.v[2], d * axis.v[0] * axis.v[2] + s * axis.v[1], 0.f,
			d * axis.v[0] * axis.v[1] + s * axis.v[2], c + d * axis.v[1] * axis.v[1], d * axis.v[1] * axis.v[2] - s * axis.v[0], 0.f,
			d * axis.v[0] * axis.v[2] - s * axis.v[1], d * axis.v[1] * axis.v[2] + s * axis.v[0], c + d * axis.v[2] * axis.v[2], 0.f);
	}

	Mat3 getScaleMatrix3(float sx, float sy, float sz) {
		return Mat3(sx, 0.f, 0.f,
					 0.f, sy, 0.f,
					 0.f, 0.f, sz);
	}
	Mat3 getScaleMatrix3(float s, const Vec3& v) {
		s -= 1.f;
		float x = v.v[0] * s;
		float y = v.v[1] * s;
		float z = v.v[2] * s;
		float vxvy = x * v.v[1];
		float vxvz = x * v.v[2];
		float vyvz = y * v.v[2];
		return Mat3(v[0] * v.v[0] + 1.f, vxvy, vxvz,
					vxvy, v[1] * v.v[1] + 1.f, vyvz,
					vxvz, vyvz, v[2] * v.v[2] + 1.f);
	}
	Mat4h getScaleMatrix4(float sx, float sy, float sz) {
		return Mat4h(sx, 0.f, 0.f, 0.f,
					0.f, sy, 0.f, 0.f,
					0.f, 0.f, sz, 0.f);
	}
	Mat4h getScaleMatrix4(float s, const Vec3& v) {
		s -= 1.f;
		float x = v.v[0] * s;
		float y = v.v[1] * s;
		float z = v.v[2] * s;
		float vxvy = x * v.v[1];
		float vxvz = x * v.v[2];
		float vyvz = y * v.v[2];
		return Mat4h(v[0] * v.v[0] + 1.f, vxvy, vxvz, 0.f,
					vxvy, v[1] * v.v[1] + 1.f, vyvz, 0.f,
					vxvz, vyvz, v[2] * v.v[2] + 1.f, 0.f);
	}

	void translate(Mat4& m, Vec3 transl) {
		m.n[3][0] += transl.v[0];
		m.n[3][1] += transl.v[1];
		m.n[3][2] += transl.v[2];
	}

	void setTranslation(Mat4& m, Vec3 transl) {
		m.n[3][0] = transl.v[0];
		m.n[3][1] = transl.v[1];
		m.n[3][2] = transl.v[2];
	}

	void transpose(Mat4& m)
	{
		float temp = m.n[0][1];
		m.n[0][1] = m.n[1][0];
		m.n[1][0] = temp;
		temp = m.n[0][2];
		m.n[0][2] = m.n[2][0];
		m.n[2][0] = temp;
		temp = m.n[0][3];
		m.n[0][3] = m.n[3][0];
		m.n[3][0] = temp;
		temp = m.n[1][2];
		m.n[2][1] = m.n[1][2];
		m.n[1][2] = temp;
		temp = m.n[1][3];
		m.n[1][3] = m.n[3][1];
		m.n[3][1] = temp;
		temp = m.n[2][3];
		m.n[2][3] = m.n[3][2];
		m.n[3][2] = temp;
	}

	Mat4 getProjectionMat(float fovY, float aspectRatio, float znear, float zfar) {
		float f = 1.f / tan(fovY / 2.f);
		return Mat4(f / aspectRatio, 0.f, 0.f, 0.f,
			0.f, f, 0.f, 0.f,
			0.f, 0.f, -(zfar + znear) / (zfar - znear), -2 * zfar * znear / (zfar - znear),
			0.f, 0.f, -1.f, 0.f);
	}
}