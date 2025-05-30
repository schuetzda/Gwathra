#include "raymain.h"
#include "gwm.h"
#include <vector>
#include <Utility/OBJMesh.h>
#include <Utility/OBJImporter.h>

namespace gwa {
	

	RayMain::RayMain() : GwaMain(), m_height(1080), m_width(1920), m_texOut(0), m_texIn(0){
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

		
		ObjMesh mesh = ObjMesh();


		OBJImporter::import_filetiny("assets/CornellBox-Original.obj", mesh, m_bvhTree);

		screenShader.create(screenVertShaderPath.c_str(), screenFragShaderPath.c_str());
		
		screenVA.create(3);
		screenVA.setArrayBuffer(0, GL_FLOAT, 2, 2, fullSreenTriangle, sizeof(float));
		computeShader.create(rayTracerComputeShaderPath.c_str());
		initComputeShaderTex();		
		glBindImageTexture(0, m_texOut, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	}
	void RayMain::render() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		computeShader.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texOut);
		glUniform1i(computeShader.getUniformLocation("tex"), 0);
		glUniform1f(computeShader.getUniformLocation("aspect"), m_width / static_cast<float>(m_height));
		glUniform1f(computeShader.getUniformLocation("tanHalfFovY"), tanHalfFovY);
		glUniform1ui(computeShader.getUniformLocation("sampleCount"), Application::Get().GetCam().getSeed());
		glUniformMatrix4fv(computeShader.getUniformLocation("invViewMx"), 1, GL_FALSE, *Application::Get().GetCam().getInvViewMx().n);
		glDispatchCompute((GLuint)m_width, (GLuint)m_height, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		screenShader.bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texOut);
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

		glBindTexture(GL_TEXTURE_2D, m_texOut);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glBindTexture(GL_TEXTURE_2D, m_texIn);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
	}
	void RayMain::cursorPositionChanged(double x, double y) {

	}
	void RayMain::mouseButtonChanged(int button, int action, int modifiers) {
		
	}

	void RayMain::keyPressed(int key, int scancode, int action, int modifiers) {

	}

	void RayMain::mouseScrolled(double x, double y) {

	}

	std::pair<int,int> RayMain::getWindowSize() {
		return std::pair<int, int>(m_width, m_height);
	}

	void RayMain::initComputeShaderTex() {
		//Window Tex
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &m_texOut);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texOut);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT,	NULL);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &m_texIn);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texIn);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
	}
}