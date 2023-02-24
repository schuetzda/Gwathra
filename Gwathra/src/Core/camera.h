#pragma once
#include "gwm.h"
#include "input.h"
namespace gwa{

	class Camera
	{
	public:
		Camera();
		void moveForward();
		void moveBackward();
		void moveRight();
		void moveLeft();
		void update();
		gwm::Mat4h getViewMX() { return viewMX; }
		int getSeed() { return seed; }

	private:
		float moveSpeed;
		int seed;
		gwm::Mat4h viewMX;
	};
}
