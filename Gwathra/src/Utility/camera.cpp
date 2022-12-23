#include "camera.h"

gwa::Camera::Camera() {
	viewMX = gwm::Mat4h(1.f);
	moveSpeed = 1.f;
}

void gwa::Camera::moveForward()
{
	gwm::translate(viewMX, gwm::Vec3(0.f, 0.f, moveSpeed));
}

void gwa::Camera::moveBackward()
{
	gwm::translate(viewMX, gwm::Vec3(0.f, 0.f, -moveSpeed));
}

void gwa::Camera::moveRight()
{
	gwm::translate(viewMX, gwm::Vec3(moveSpeed, 0.f, 0.f));
}

void gwa::Camera::moveLeft()
{
	gwm::translate(viewMX, gwm::Vec3(-moveSpeed, 0.f, 0.f));
}


