#include "raymain.h"

namespace gwa {

	RayMain::RayMain() : GwaMain(){
		
	}

	void RayMain::init() {
		const float fullSreenTriangle[] = {
			-1.f, -1.f,      // 1. vertex (x,y)
			 3.f, -1.f,      // 2. vertex (x,y)
			-1.f,  3.f,      // 3. vertex (x,y)
		};

		const std::string screenVertShaderPath = std::string("src/resources/screen.vert");
		const std::string screenFragShaderPath = std::string("src/resources/screen.frag");

		screenShader.create(screenVertShaderPath.c_str(), screenFragShaderPath.c_str());
		
		screenVA.create(3);
		screenVA.setArrayBuffer(0, GL_FLOAT, 2, 2, fullSreenTriangle, sizeof(float));
	}
	void RayMain::render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		screenShader.bind();
		screenVA.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		screenVA.release();
	}
	void RayMain::deactivate() {

	}

	void RayMain::windowSizeChanged(int width, int height) {
		glViewport(0, 0, width, height);
	}
	void RayMain::cursorPositionChanged(double x, double y) {

	}
	void RayMain::mouseButtonChanged(int button, int action, int modifiers) {

	}
	void RayMain::mouseScrolled(double x, double y) {

	}
}