#pragma once
#include "Gwathra.h"
namespace gwa {
	class CubeMain : public GwaMain
	{
	public:
		CubeMain();
		virtual ~CubeMain() = default;

		virtual void windowSizeChanged(int width, int height);
		virtual void init();
		virtual void render();
		virtual void deactivate();
	};
}
