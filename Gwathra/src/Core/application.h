#pragma once
#include "GwaMain.h"

namespace gwa {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void run();

		

	protected:
		GwaMain main;
	};
	Application* createApplication();
}

