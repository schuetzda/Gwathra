#pragma once
#include <iostream>

namespace gwa {
	class GwaMain
	{
	public:
		virtual ~GwaMain() {};
		GwaMain() {};
		virtual void init(){}
		virtual void render(){}
		virtual void deactivate(){}

		virtual void windowSizeChanged(int width, int height) {}
		virtual void cursorPositionChanged(double x, double y) {}
		virtual void mouseButtonChanged(int button, int action, int modifiers) {}
		virtual void keyPressed(int key, int scancode, int action, int modifiers){}
		virtual void mouseScrolled(double x, double y) {}
	private:
	};
}