#include "window.h"
#include "GLFW/glfw3.h"
#include <iostream>

static GLFWwindow* m_window;
namespace gwa {
	static void resizeWindow(GLFWwindow* window, int width, int height) {
		std::cout << "Test";
	}

	Window::Window(const char* title, const uint32_t width, const uint32_t height) : title(title), width(width), height(height)  {
		initWindow();
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::initWindow() {
		// glfw: initialize and configure
		glfwInit();
		glfwSetTime(0);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		m_window = glfwCreateWindow(width, height, "SimpleCubeRenderer", NULL, NULL);

		if (m_window == NULL)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);

		glfwSetFramebufferSizeCallback(m_window, resizeWindow);
	}

	void Window::update() {
		glfwPollEvents();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(m_window);
	}
}