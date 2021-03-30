#pragma once
#include "Gwathra.h"

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
		virtual void mouseScrolled(double x, double y);

	private:
		void initComputeShaderTex();

		Shader screenShader, computeShader;
		VertexArray screenVA;
		uint32_t m_width, m_height;
		GLuint tex_out, tex_in;
		uint32_t seed;
	};
}
