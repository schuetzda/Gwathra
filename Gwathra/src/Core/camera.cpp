#include "camera.h"
#include "input.h"

namespace gwa {

	Camera::Camera() {
		m_invView = gwm::Mat4h(1.f);
		moveSpeed = .5f;
		seed = 0;
		gwm::translate(m_invView, gwm::Vec3(0.0f, 0.f, -8.f));
	}

	void Camera::update() {
		seed++;

		
		const int mouseButtonPressed = Input::IsMouseButtonPressed(1);
		if (mouseButtonPressed > 0) {
			const std::tuple<int, int> pos = Input::GetMousePosition();

		}
			

		if (Input::IsKeyPressed(87)) {
			moveForward();
			seed = 0;
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
		gwm::translate(m_invView, gwm::Vec3(0.f, 0.f, moveSpeed));
		seed = 0;
	}

	void Camera::moveBackward()
	{
		gwm::translate(m_invView, gwm::Vec3(0.f, 0.f, -moveSpeed));
		seed = 0;
	}

	void Camera::moveRight()
	{
		gwm::translate(m_invView, gwm::Vec3(moveSpeed, 0.f, 0.f));
		seed = 0;
	}

	void Camera::moveLeft()
	{
		gwm::translate(m_invView, gwm::Vec3(-moveSpeed, 0.f, 0.f));
		seed = 0;
	}
}

