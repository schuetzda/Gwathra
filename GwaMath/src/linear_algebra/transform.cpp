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

		return Mat3(c + d * axis.x * axis.x, d * axis.x * axis.y - s * axis.z, d * axis.x * axis.z + s * axis.y,
					d * axis.x * axis.y + s * axis.z, c + d * axis.y * axis.y, d * axis.y * axis.z - s * axis.x,
					d * axis.x * axis.z - s * axis.y, d * axis.y * axis.z + s * axis.x, c + d * axis.z * axis.z);
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

		return Mat4h(c + d * axis.x * axis.x, d * axis.x * axis.y - s * axis.z, d * axis.x * axis.z + s * axis.y, 0.f,
			d * axis.x * axis.y + s * axis.z, c + d * axis.y * axis.y, d * axis.y * axis.z - s * axis.x, 0.f,
			d * axis.x * axis.z - s * axis.y, d * axis.y * axis.z + s * axis.x, c + d * axis.z * axis.z, 0.f);
	}

	Mat3 getScaleMatrix3(float sx, float sy, float sz) {
		return Mat3(sx, 0.f, 0.f,
					 0.f, sy, 0.f,
					 0.f, 0.f, sz);
	}
	Mat3 getScaleMatrix3(float s, const Vec3& v) {
		s -= 1.f;
		float x = v.x * s;
		float y = v.y * s;
		float z = v.z * s;
		float vxvy = x * v.y;
		float vxvz = x * v.z;
		float vyvz = y * v.z;
		return Mat3(x * v.x + 1.f, vxvy, vxvz,
					vxvy, y * v.y + 1.f, vyvz,
					vxvz, vyvz, z * v.z + 1.f);
	}
	Mat4h getScaleMatrix4(float sx, float sy, float sz) {
		return Mat4h(sx, 0.f, 0.f, 0.f,
					0.f, sy, 0.f, 0.f,
					0.f, 0.f, sz, 0.f);
	}
	Mat4h getScaleMatrix4(float s, const Vec3& v) {
		s -= 1.f;
		float x = v.x * s;
		float y = v.y * s;
		float z = v.z * s;
		float vxvy = x * v.y;
		float vxvz = x * v.z;
		float vyvz = y * v.z;
		return Mat4h(x * v.x + 1.f, vxvy, vxvz, 0.f,
					vxvy, y * v.y + 1.f, vyvz, 0.f,
					vxvz, vyvz, z * v.z + 1.f, 0.f);
	}

	void translate(Mat4& m, Vec3 transl) {
		m.n[3][0] += transl.x;
		m.n[3][1] += transl.y;
		m.n[3][2] += transl.z;
	}

	void setTranslation(Mat4& m, Vec3 transl) {
		m.n[3][0] = transl.x;
		m.n[3][1] = transl.y;
		m.n[3][2] = transl.z;
	}

	Mat4 getProjectionMat(float fovY, float aspectRatio, float znear, float zfar) {
		float f = 1.f / tan(fovY / 2.f);
		return Mat4(f / aspectRatio, 0.f, 0.f, 0.f,
			0.f, f, 0.f, 0.f,
			0.f, 0.f, -(zfar + znear) / (zfar - znear), -2 * zfar * znear / (zfar - znear),
			0.f, 0.f, -1.f, 0.f);
	}
}