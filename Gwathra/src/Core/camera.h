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
		gwm::Mat4 getInvViewMx() { return m_invView; }
		gwm::Mat4 getInvProjMx() { return m_invProjection; }
		int getSeed() { return seed; }

	private:
		float moveSpeed;
		int seed;
		

		float m_fovY= 45.0f;
		float m_aspect = 16.f / 9.f;
		float m_zNear = 0.1f;
		float m_zFar = 100.0f;

		gwm::Mat4 m_invView{ 1.f };
		gwm::Mat4 m_invProjection{ 1.f };
		gwm::Mat4 m_Projection{ 1.f };
	};
}
