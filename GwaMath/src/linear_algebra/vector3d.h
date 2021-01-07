#pragma once
namespace gwm
{
	struct Vec3
	{
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;

		Vec3() : x(0), y(0), z(0) {}
		Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

		float& operator [](const int i);
		const float& operator [](const int i) const;
		Vec3& operator*=(const float s);
		Vec3& operator/=(const float s);
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);

	};

	const float magnitude(const Vec3& v);
	void normalize(Vec3& v);
	const float dot(const Vec3& a, const Vec3& b);
	const Vec3 cross(const Vec3& a, const Vec3& b);
	const Vec3 project(const Vec3& a, const Vec3& b);
	const Vec3 reject(const Vec3& a, const Vec3& b);

	Vec3 operator *(Vec3 v, float s);
	Vec3 operator *(float s, Vec3 v);
	Vec3 operator /(Vec3 v, float s);
	Vec3 operator /(float s, Vec3 v);
	Vec3 operator +(const Vec3& a, const Vec3& b);
	Vec3 operator -(const Vec3& a, const Vec3& b);
	Vec3 operator -(const Vec3& a);
}