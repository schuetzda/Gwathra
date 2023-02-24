#include "input.h"
#include "application.h"
#include <GLFW/glfw3.h>

namespace gwa {

	bool Input::IsKeyPressed(const int key)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::tuple<float, float> Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
}