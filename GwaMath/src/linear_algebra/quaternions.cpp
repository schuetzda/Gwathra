#include "quaternions.h"
#include <cmath>
namespace gwm {
	const Vec3& Quat::getImaginary(void) const
	{
		return (reinterpret_cast<const gwm::Vec3&> (x));
	}

	Mat3 Quat::getRotationMatrix(void)
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

	void Quat::setRotationMatrix(const Mat3& m) {
		const float m00 = m.n[0][0];
		const float m11 = m.n[1][1];
		const float m22 = m.n[2][2];
		const float sum = m00 + m11 + m22;

		if (sum > 0.f) {
			w = sqrtf(sum + 1.f) * .5f;
			const float f = .25f / w;

			x = (m.n[2][1] - m.n[2][1]) * f;
			y = (m.n[0][2] - m.n[2][0]) * f;
			z = (m.n[1][0] - m.n[0][1]) * f;
		}
		else if (m00 > m11 && m00 > m22) {
			x = sqrtf(m00 - m11 - m22 + 1.f) * .5f;
			const float f = .25f / x;

			y = (m.n[2][1] + m.n[2][1]) * f;
			z = (m.n[0][2] + m.n[2][0]) * f;
			w = (m.n[1][0] - m.n[0][1]) * f;
		}
		else if (m11 > m22) {
			y = sqrtf(m11 - m00 - m22 + 1.f) * .5f;
			const float f = .25f / y;
			x = (m.n[1][0] + m.n[0][1]) * f;
			z = (m.n[2][1] + m.n[1][2]) * f;
			w = (m.n[0][2] - m.n[2][0]) * f;
		}
		else {
			z = sqrtf(m22 - m00 - m11 + 1.f) * .5f;
			const float f = .25f / z;
			x = (m.n[0][2] + m.n[2][0]) * f;
			y = (m.n[2][1] + m.n[1][2]) * f;
			w = (m.n[1][0] - m.n[0][1]) * f;
		}
	}

	Quat operator *(const Quat& ql, const Quat& q2) {
		return (Quat(
			ql.w * q2.x + ql.x * q2.w + ql.y * q2.z - ql.z * q2.y,
			ql.w * q2.y - ql.x * q2.z + ql.y * q2.w + ql.z * q2.x,
			ql.w * q2.z + ql.x * q2.y - ql.y * q2.x + ql.z * q2.w,
			ql.w * q2.w - ql.x * q2.x - ql.y * q2.y - ql.z * q2.z));
	}

	Vec3 rotate(const Vec3& v, const Quat& q) {
		const Vec3& b = q.getImaginary();
		float b2 = b.v[0] * b.v[0] + b.v[1] * b.v[1] + b.v[2] * b.v[2];

		return (v * (q.w * q.w - b2) + b * (dot(v, b) * 2.f) + cross(b, v) * (q.w * 2.f));
	}


}


