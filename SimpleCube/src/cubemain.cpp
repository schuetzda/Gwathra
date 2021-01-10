#include <glad/glad.h>
#include "cubemain.h"
namespace gwa {
	CubeMain::CubeMain() : GwaMain() {
		
	}

	void CubeMain::windowSizeChanged(int width, int height) {
		int a = 0;
	}

	void CubeMain::init() {

	}

	void CubeMain::render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void CubeMain::deactivate() {

	}
}