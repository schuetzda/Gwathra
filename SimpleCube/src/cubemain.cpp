#include <glad/glad.h>
#include "cubemain.h"

namespace gwa {
	CubeMain::CubeMain() : GwaMain(), mouseX(0.), mouseY(0.) {
		
	}

	void CubeMain::init() {
		const float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		const std::string shaderPath = "src/resources/";
		const std::string vertexShaderPath = shaderPath + "cube.vert";
		const std::string fragShaderPath = shaderPath + "cube.frag";

		shaderTriangle.create(vertexShaderPath.c_str(), fragShaderPath.c_str());
		vaTriangle.create(36);
		vaTriangle.setArrayBuffer(0, GL_FLOAT, 3, 6, vertices, sizeof(float));
		vaTriangle.setArrayBuffer(1, GL_FLOAT, 3, 6, vertices, 4, (void*)(3 * sizeof(float)));

		modelMX = gwm::Mat4h(1.f), scaleMX = gwm::Mat4h(1.f), translMX = gwm::Mat4h(1.f), rotateMX = gwm::Mat4h(1.f);
		lightPos = gwm::Vec3(1.f, 1.f, 1.f);
		glEnable(GL_DEPTH_TEST);
	}

	void CubeMain::render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderTriangle.bind();

		gwm::Mat4 invViewMX = Application::Get().GetCam().getInvViewMx();
		gwm::Mat4 viewMX = gwm::inverse(invViewMX);
		gwm::Mat4 projMX = gwm::getProjectionMat(0.4f, aspectRatio, 0.1f, 100.f);
		glUniformMatrix4fv(shaderTriangle.getUniformLocation("modelMX"), 1, GL_FALSE, *modelMX.n);
		glUniformMatrix4fv(shaderTriangle.getUniformLocation("viewMX"), 1, GL_FALSE, *viewMX.n);
		glUniformMatrix4fv(shaderTriangle.getUniformLocation("projMX"), 1, GL_FALSE, *projMX.n);
		glUniform3fv(shaderTriangle.getUniformLocation("lightPos"),1, &lightPos.v[0]);
		glUniform3f(shaderTriangle.getUniformLocation("viewPos"), invViewMX(0, 3), invViewMX(1, 3), invViewMX(2, 3));
		vaTriangle.bind();

		glClear(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, 0, 0);
		glStencilOp(GL_KEEP, GL_INCR, GL_INCR);

		glEnable(GL_STENCIL_TEST);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		vaTriangle.release();
	}

	void CubeMain::deactivate() {

	}

	void CubeMain::windowSizeChanged(int width, int height) {
		wHeight = height;
		wWidth = width;
		aspectRatio = width / static_cast<float> (wHeight);
		glViewport(0, 0, width, height);
	}

	void CubeMain::cursorPositionChanged(double x, double y) {
	}

	void CubeMain::mouseButtonChanged(int button, int action, int modifiers) {
	}



	void CubeMain::mouseScrolled(double x, double y) {
	
	}
	std::pair<int, int> CubeMain::getWindowSize()
	{
		return std::pair<int, int>(wWidth, wHeight);
	}
}