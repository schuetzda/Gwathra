#include "quaternions.h"
namespace gwm {
	const Vec3& Quaternion::getImaginary(void) const
	{
		return (reinterpret_cast<const gwm::Vec3&> (x));
	}

	Mat3 Quaternion::getRotationMatrix(void)
	{
		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;
		
		return (Mat3(1.f - 2.f * (y2 * z2), 2.f * (xy + wz), 2.f * (xz + wy),
			2.f * (xy + wz), 1.f - 2.f * (x2 + z2), 2.f * (yz + wx),
			2.f * (xz - wy), 2.f * (yz + wx), 1.f - 2.f * (x2 + y2)));
	}

	Quaternion operator *(const Quaternion& ql, const Quaternion& q2) {
		return (Quaternion(
			ql.w * q2.x + ql.x * q2.w + ql.y * q2.z - ql.z * q2.y,
			ql.w * q2.y - ql.x * q2.z + ql.y * q2.w + ql.z * q2.x,
			ql.w * q2.z + ql.x * q2.y - ql.y * q2.x + ql.z * q2.w,
			ql.w * q2.w - ql.x * q2.x - ql.y * q2.y - ql.z * q2.z));
	}

	Vec3 rotate(const Vec3& v, const Quaternion& q) {
		const Vec3& b = q.getImaginary();
		float b2 = b.v[0] * b.v[0] + b.v[1] * b.v[1] + b.v[2] * b.v[2];
		return (v * (q.w * q.w - b2) + b * (dot(v, b) * 2.0F) + cross(b, v) * (q.w * 2.0F));
	}
}


