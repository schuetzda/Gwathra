#pragma once

#include "Gwathra.h"
#include "gwm.h"
namespace gwa {
	class CubeMain : public GwaMain
	{
	public:
		CubeMain();

		virtual void init();
		virtual void render();
		virtual void deactivate();

		virtual void windowSizeChanged(int width, int height);
		virtual void cursorPositionChanged(double x, double y);
		virtual void mouseButtonChanged(int button, int action, int modifiers);
		void mouseScrolled(double x, double y);
		virtual std::pair<int, int> getWindowSize();
	private:
		gwm::Mat4 modelMX, rotateMX, translMX, scaleMX;
		gwm::Vec3 lightPos;

		VertexArray vaTriangle;
		Shader shaderTriangle;
		double mouseX, mouseY;
		uint32_t wWidth = 1920;
		uint32_t wHeight = 1080;
		float aspectRatio = wWidth / static_cast<float>(wHeight);

		bool mouseLeftDown = false;
		bool mouseMiddleDown = false;
		bool mouseRightDown = false;
	};
}
