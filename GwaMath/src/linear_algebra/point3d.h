#pragma once
#include "vector3d.h"

namespace gwm
{
	struct Pnt3:Vec3
	{
		Pnt3() = default;
		Pnt3(const float x, const float y, const float z) : Vec3(x, y, z) {}
	};
	Pnt3 operator +(const Pnt3& a, const Vec3& b);
	Vec3 operator -(const Pnt3& a, const Vec3& b);
	Pnt3 operator *(Pnt3 v, float s);
	Pnt3 operator *(float s, Pnt3 v);
	Pnt3 operator /(Pnt3 v, float s);
	Pnt3 operator /(float s, Pnt3 v);
}

