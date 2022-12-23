#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <iostream>

static uint32_t SCR_WIDTH = 1920;
static uint32_t SCR_HEIGHT = 1080;
static GLFWwindow* window;
//TODO: Window creation and Input events in seperate classes
namespace gwa {
	Application::Application(GwaMain *const main, const std::string& name): main(main), name(name) {
		
	}

	Application::~Application() {
		glfwTerminate();
		delete main;
	}

	void Application::run() {
		
		initGLFW();
		
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);

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

		glfwSetKeyCallback(window,
			[](GLFWwindow* window, int key,int scancode, int action, int modifiers) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(window));
				main.keyPressed(key, scancode, action, modifiers);
			}
		);

		glfwSetScrollCallback(window,
			[](GLFWwindow* window, double x, double y) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(window));
				main.mouseScrolled(x, y);
			}
		);
		
		main->init();
		double previousTime = glfwGetTime();
		double avg100 = 0.;
		int count = 1;
		while (!glfwWindowShouldClose(window))
		{
			main->render();
			glfwPollEvents();
			glfwSwapBuffers(window);
			double currentTime = glfwGetTime();
			//std::cout << currentTime - previousTime << "\n";
			avg100 += currentTime - previousTime;
			previousTime = currentTime;
			if (count % 50 == 0) {
				count = 0;
				std::cout << avg100/50. << " ("<< (1.f/(avg100/50))<<")  " << "\n";
				avg100 = 0.;
			}
			count++;
		}

		main->deactivate();
		glfwTerminate();
	}

	void Application::initGLFW() {
		// glfw: initialize and configure
		glfwInit();
		glfwSetTime(0);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}

	
	std::pair<double,double> Application::GetMousePosition() {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	bool Application::IsKeyPressed(const int key){
		auto state = glfwGetKey(window,key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Application::IsMouseButtonPressed(const int button){
		auto state = glfwGetMouseButton(window,button);
		return state == GLFW_PRESS;
	}
}