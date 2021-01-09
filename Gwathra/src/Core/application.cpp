#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GwaMain.h"
#include "Application.h"
#include <iostream>



const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

namespace gwa {
	
	void initGLFW() {
		// glfw: initialize and configure
		glfwInit();
		glfwSetTime(0);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_SAMPLES, 0);
		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_STENCIL_BITS, 8);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::run() {
		initGLFW();
		// glfw window creation
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SimpleCubeRenderer", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW windowa" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		main.init();

		while (!glfwWindowShouldClose(window))
		{
			main.render();
			glfwPollEvents();
			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwSwapBuffers(window);
		}
		main.deactivate();
		glfwTerminate();
	}
}