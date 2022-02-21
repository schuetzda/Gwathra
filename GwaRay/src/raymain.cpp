#include "raymain.h"
#include "gwm.h"
#include <vector>
#include <Utility/OBJImporter.h>
namespace gwa {

	RayMain::RayMain() : GwaMain(), m_height(1080), m_width(1920), tex_out(0), seed(0), tex_in(0){
		
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

		OBJMesh mesh = OBJMesh();

		OBJImporter::import_file("assets/CornellBox-Original.obj", &mesh);

		screenShader.create(screenVertShaderPath.c_str(), screenFragShaderPath.c_str());
		
		screenVA.create(3);
		screenVA.setArrayBuffer(0, GL_FLOAT, 2, 2, fullSreenTriangle, sizeof(float));
		computeShader.create(rayTracerComputeShaderPath.c_str());
		initComputeShaderTex();		
		glBindImageTexture(0, tex_out, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	}
	void RayMain::render() {
		//View/Projection Matrices
		gwm::Mat4h viewMX = gwm::Mat4h(1.f);
		gwm::translate(viewMX, gwm::Vec3(0.0f, 0.f, -10.f));
		const gwm::Mat4 projMX = gwm::getProjectionMat(0.4f, m_width / static_cast<float>(m_height), 0.1f, 100.f);
		const gwm::Mat4 invProjViewMX = gwm::inverse(projMX * viewMX);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		computeShader.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_out);
		glUniform1i(screenShader.getUniformLocation("tex"), 0);
		glUniform1ui(computeShader.getUniformLocation("sampleCount"), seed);
		glUniformMatrix4fv(computeShader.getUniformLocation("invProjViewMX"), 1, GL_FALSE, *invProjViewMX.n);
		glDispatchCompute((GLuint)m_width, (GLuint)m_height, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		screenShader.bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_out);
		glUniform1i(screenShader.getUniformLocation("tex"), 0);
		screenVA.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		screenVA.release();

		seed++;
	}
	void RayMain::deactivate() {

	}

	void RayMain::windowSizeChanged(int width, int height) {
		glViewport(0, 0, width, height);
		m_width = width;
		m_height = height;

		glBindTexture(GL_TEXTURE_2D, tex_out);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glBindTexture(GL_TEXTURE_2D, tex_in);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);

		seed = 0;
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
		glGenTextures(1, &tex_out);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_out);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT,	NULL);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &tex_in);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_in);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
	}
}