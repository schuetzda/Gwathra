#include "camera.h"
#include "input.h"
#include <iostream>


namespace gwa {
	

	Camera::Camera(): m_moveSpeed(.5f), m_seed(0), m_invView(gwm::Mat4h(1)) {
		m_invView = gwm::Mat4h(1.f);

		gwm::translate(m_invView, gwm::Vec3(0.0f, 0.f, -8.f));
	}

	void Camera::update() {
		m_seed++;

		
		const int mouseButtonPressed = Input::IsMouseButtonPressed(0);
		if (pressed && mouseButtonPressed == 0)
			pressed = false;

		if (mouseButtonPressed > 0) {

			std::pair<float, float> mousePos = Input::GetMousePosition();
			if (pressed) {
				const float deltaX = (mousePos.first - m_prevMousePos.first)* 0.0003f;
				const float deltaY = (mousePos.second - m_prevMousePos.second) * 0.0003f;
				m_invView = m_invView * gwm::getRotMatrix4(deltaX, gwm::Vec3(m_invView.n[1][0], m_invView.n[1][1], m_invView.n[1][2]));
				m_invView = m_invView * gwm::getRotMatrix4(deltaY, gwm::Vec3(m_invView.n[0][0], m_invView.n[0][1], m_invView.n[0][2]));
				m_seed = 0;
			}
			else {
				pressed = true;
			}
			m_prevMousePos = mousePos;
		}
			

		if (Input::IsKeyPressed(87)) {
			moveForward();
		}
		if (Input::IsKeyPressed(83)) {
			moveBackward();
		}
		if (Input::IsKeyPressed(65)) {
			moveLeft();
		}
		if (Input::IsKeyPressed(68)) {
			moveRight();
		}

	}

	void Camera::moveForward()
	{
		gwm::translate(m_invView, gwm::Vec3(m_invView.n[2][0], m_invView.n[2][1], m_invView.n[2][2])* .3f);
		m_seed = 0;
	}

	void Camera::moveBackward()
	{
		gwm::translate(m_invView, -gwm::Vec3(m_invView.n[2][0], m_invView.n[2][1], m_invView.n[2][2]) * .3f);
		m_seed = 0;
	}

	void Camera::moveRight()
	{
		gwm::translate(m_invView, gwm::Vec3(m_invView.n[0][0], m_invView.n[0][1], m_invView.n[0][2]) * .3f);
		m_seed = 0;
	}

	void Camera::moveLeft()
	{
		gwm::translate(m_invView, -gwm::Vec3(m_invView.n[0][0], m_invView.n[0][1], m_invView.n[0][2]) * .3f);
		m_seed = 0;
	}
}

