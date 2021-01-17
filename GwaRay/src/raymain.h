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
		Shader screenShader;
		VertexArray screenVA;
	};
}
