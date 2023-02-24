#include "camera.h"
#include "input.h"

namespace gwa {

	Camera::Camera() {
		viewMX = gwm::Mat4h(1.f);
		moveSpeed = 0.5f;
		seed = 0;
		gwm::translate(viewMX, gwm::Vec3(0.0f, 0.f, -50.f));
	}

	void Camera::update() {
		seed++;
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
		gwm::translate(viewMX, gwm::Vec3(0.f, 0.f, moveSpeed));
		seed = 0;
	}

	void Camera::moveBackward()
	{
		gwm::translate(viewMX, gwm::Vec3(0.f, 0.f, -moveSpeed));
		seed = 0;
	}

	void Camera::moveRight()
	{
		gwm::translate(viewMX, gwm::Vec3(moveSpeed, 0.f, 0.f));
		seed = 0;
	}

	void Camera::moveLeft()
	{
		gwm::translate(viewMX, gwm::Vec3(-moveSpeed, 0.f, 0.f));
		seed = 0;
	}
}

