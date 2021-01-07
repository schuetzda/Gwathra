#include "point3d.h"
namespace gwm
{

	Pnt3 operator +(const Pnt3& a, const Vec3& b)
	{
		return (Pnt3(a.x + b.x, a.y + b.y, a.z + b.z));
	}

	 Vec3 operator -(const Pnt3& a, const Vec3& b)
	{
		return (Vec3(a.x - b.x, a.y - b.y, a.z - b.z));
	}

	 Pnt3 operator *(Pnt3 v, const float s)
	 {
		 v.x *= s;
		 v.y *= s;
		 v.z *= s;
		 return v;
	 }

	 Pnt3 operator *(float s, Pnt3 v)
	 {
		 return v * s;
	 }

	 Pnt3 operator /(Pnt3 v, float s)
	 {
		 v.x /= s;
		 v.y /= s;
		 v.z /= s;
		 return v;
	 }
	 Pnt3 operator /(float s, Pnt3 v)
	 {
		 v.x = s / v.x;
		 v.y = s / v.y;
		 v.z = s / v.z;
		 return v;
	 }

}