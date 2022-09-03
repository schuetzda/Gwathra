#include "camera.h"

gwa::Camera::Camera() {
	viewMX = gwm::Mat4h(1.f);
	moveSpeed = 1.f;
}

void gwa::Camera::moveForward()
{
	gwm::transpose(viewMX);
	gwm::translate(viewMX, gwm::Vec3(0.f, 0.f, moveSpeed));
	gwm::transpose(viewMX);
}

void gwa::Camera::moveBackward()
{
	gwm::transpose(viewMX);
	gwm::translate(viewMX, gwm::Vec3(0.f, 0.f, -moveSpeed));
	gwm::transpose(viewMX);
}

void gwa::Camera::moveRight()
{
	gwm::transpose(viewMX);
	gwm::translate(viewMX, gwm::Vec3(moveSpeed, 0.f, 0.f));
	gwm::transpose(viewMX);
}

void gwa::Camera::moveLeft()
{
	gwm::transpose(viewMX);
	gwm::translate(viewMX, gwm::Vec3(-moveSpeed, 0.f, 0.f));
	gwm::transpose(viewMX);
}


