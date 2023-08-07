#pragma once
#include "Gwathra.h"
#include <Utility/bvhtree.h>

namespace gwa {
	class RayMain : public GwaMain
	{
	public:
		RayMain();

		virtual void init();
		virtual void render();
		virtual void deactivate();

		virtual void windowSizeChanged(int width, int height);
		virtual void cursorPositionChanged(double x, double y);
		virtual void mouseButtonChanged(int button, int action, int modifiers);
		virtual void keyPressed(int key, int scancode, int action, int modifiers);
		virtual void mouseScrolled(double x, double y);
		virtual std::pair<int, int> getWindowSize();

	private:
		void initComputeShaderTex();

		Shader screenShader, computeShader;
		VertexArray screenVA;
		uint32_t m_width, m_height;
		GLuint m_texOut, m_texIn;
		BVHTree m_bvhTree;
		const float fovY = 0.4f;
		const float tanHalfFovY = tan(fovY / 2.f);
	};
}
