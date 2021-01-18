#include "raymain.h"

namespace gwa {

	RayMain::RayMain() : GwaMain(), m_height(1080), m_width(1920), tex_output(0){
		
	}

	void RayMain::init() {
		const float fullSreenTriangle[] = {
			-1.f, -1.f,      // 1. vertex (x,y)
			 3.f, -1.f,      // 2. vertex (x,y)
			-1.f,  3.f,      // 3. vertex (x,y)
		};

		const std::string screenVertShaderPath = std::string("src/resources/screen.vert");
		const std::string screenFragShaderPath = std::string("src/resources/screen.frag");
		const std::string rayTracerComputeShaderPath = std::string("src/resources/raytracer.comp");
		screenShader.create(screenVertShaderPath.c_str(), screenFragShaderPath.c_str());
		
		screenVA.create(3);
		screenVA.setArrayBuffer(0, GL_FLOAT, 2, 2, fullSreenTriangle, sizeof(float));
		computeShader.create(rayTracerComputeShaderPath.c_str());
		initComputeShaderTex();
		computeShader.bind();
		glBindImageTexture(0, tex_output, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	}
	void RayMain::render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		computeShader.bind();
		glDispatchCompute((GLuint)m_width, (GLuint)m_height, 1);

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		screenShader.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_output);
		glUniform1i(screenShader.getUniformLocation("tex"), 0);
		screenVA.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		screenVA.release();
	}
	void RayMain::deactivate() {

	}

	void RayMain::windowSizeChanged(int width, int height) {
		glViewport(0, 0, width, height);
		m_width = width;
		m_height = height;
	}
	void RayMain::cursorPositionChanged(double x, double y) {

	}
	void RayMain::mouseButtonChanged(int button, int action, int modifiers) {

	}
	void RayMain::mouseScrolled(double x, double y) {

	}

	void RayMain::initComputeShaderTex() {
		//Window Tex
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &tex_output);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_output);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT,	NULL);
	}
}