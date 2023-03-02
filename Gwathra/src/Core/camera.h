#pragma once
#include "gwm.h"
#include "input.h"
#include <utility>

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
		gwm::Mat4 getInvViewMx() { return m_invView; }
		int getSeed() { return m_seed; }

	private:
		float m_moveSpeed;
		int m_seed;
		std::pair<int, int> m_prevMousePos;
		gwm::Mat4 m_invView{ 1.f };
		bool pressed = false;
	};
}
