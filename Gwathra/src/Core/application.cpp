#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <iostream>

static uint32_t SCR_WIDTH = 1920;
static uint32_t SCR_HEIGHT = 1080;

namespace gwa {
	Application::Application(GwaMain *const main, const std::string& name): main(main), name(name) {
		
	}

	Application::~Application() {
		glfwTerminate();
		delete main;
	}

	void Application::run() {
		initGLFW();
		GLFWwindow* window;
		window = glfwCreateWindow(SCR_WIDTH, 1080, "SimpleCubeRenderer", NULL, NULL);

		if (window == NULL)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		glfwSetWindowUserPointer(window, this);

		glfwSetWindowUserPointer(window, main);

		glfwSetFramebufferSizeCallback(window,
			[](GLFWwindow* window, int width, int height) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(window));
				main.windowSizeChanged(width, height);
			}
		);

		glfwSetCursorPosCallback(window,
			[](GLFWwindow* window, double x, double y) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(window));
				main.cursorPositionChanged(x, y);
			}
		);

		glfwSetMouseButtonCallback(window,
			[](GLFWwindow* window, int button, int action, int modifiers) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(window));
				main.mouseButtonChanged(button, action, modifiers);
			}
		);

		glfwSetScrollCallback(window,
			[](GLFWwindow* window, double x, double y) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(window));
				main.mouseScrolled(x, y);
			}
		);
		
		main->init();

		while (!glfwWindowShouldClose(window))
		{
			main->render();
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		main->deactivate();
		glfwTerminate();
	}

	void Application::initGLFW() {
		// glfw: initialize and configure
		glfwInit();
		glfwSetTime(0);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}
}