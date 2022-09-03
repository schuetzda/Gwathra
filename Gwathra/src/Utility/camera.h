#pragma once
#include "gwm.h"
namespace gwa{
	class Camera
	{
	public:
		Camera();
		gwm::Mat4h viewMX;
		void moveForward();
		void moveBackward();
		void moveRight();
		void moveLeft();

	private:
		float moveSpeed;
	};
}
