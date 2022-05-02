#include "point3d.h"
namespace gwm
{

	Pnt3 operator +(const Pnt3& a, const Vec3& b)
	{
		return (Pnt3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]));
	}

	 Vec3 operator -(const Pnt3& a, const Vec3& b)
	{
		return (Vec3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]));
	}

	 Pnt3 operator *(Pnt3 v, const float s)
	 {
		 v.v[0] *= s;
		 v.v[1] *= s;
		 v.v[2] *= s;
		 return v;
	 }

	 Pnt3 operator *(float s, Pnt3 v)
	 {
		 return v * s;
	 }

	 Pnt3 operator /(Pnt3 v, float s)
	 {
		 v.v[0] /= s;
		 v.v[1] /= s;
		 v.v[2] /= s;
		 return v;
	 }
	 Pnt3 operator /(float s, Pnt3 v)
	 {
		 v.v[0] = s / v.v[0];
		 v.v[1] = s / v.v[1];
		 v.v[2] = s / v.v[2];
		 return v;
	 }

}