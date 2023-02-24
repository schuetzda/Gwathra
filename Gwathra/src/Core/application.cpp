#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Application.h"
#include <iostream>


static uint32_t SCR_WIDTH = 1920;
static uint32_t SCR_HEIGHT = 1080;
//TODO: Window creation and Input events in seperate classes


namespace gwa {
	static GLFWwindow* m_window = nullptr;
	Application* Application::s_Instance = nullptr;

	Application::Application(GwaMain *const main, const std::string& name): main(main), name(name), cam(Camera()) {
		s_Instance = this;
		init();
	}

	Application::~Application() {
		glfwTerminate();
		delete main;
	}

	void Application::init() {
		initGLFW();

		m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);

		if (m_window == NULL)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		glfwSetWindowUserPointer(m_window, this);

		glfwSetWindowUserPointer(m_window, main);

		glfwSetFramebufferSizeCallback(m_window,
			[](GLFWwindow* m_window, int width, int height) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(m_window));
		main.windowSizeChanged(width, height);
			}
		);

		glfwSetCursorPosCallback(m_window,
			[](GLFWwindow* m_window, double x, double y) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(m_window));
		main.cursorPositionChanged(x, y);
			}
		);

		glfwSetMouseButtonCallback(m_window,
			[](GLFWwindow* m_window, int button, int action, int modifiers) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(m_window));
		main.mouseButtonChanged(button, action, modifiers);
			}
		);

		glfwSetKeyCallback(m_window,
			[](GLFWwindow* m_window, int key, int scancode, int action, int modifiers) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(m_window));
		main.keyPressed(key, scancode, action, modifiers);
			}
		);

		glfwSetScrollCallback(m_window,
			[](GLFWwindow* m_window, double x, double y) {
				GwaMain& main = *(GwaMain*)(glfwGetWindowUserPointer(m_window));
		main.mouseScrolled(x, y);
			}
		);

		main->init();
	}

	void Application::run() {
		
		
		double previousTime = glfwGetTime();
		double avg100 = 0.;
		int count = 1;
		while (!glfwWindowShouldClose(m_window))
		{
			cam.update();
			main->render();
			glfwPollEvents();
			glfwSwapBuffers(m_window);
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

	void* Application::GetNativeWindow()
	{
		return m_window;
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
}
