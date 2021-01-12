#pragma once
#include "GwaMain.h"
#include <string>

int main(int argc, char** argv);

namespace gwa {
	class Application
	{
	public:
		Application(GwaMain *const main, const std::string& name);

		virtual ~Application();
		void run();
	private:
		void initGLFW();
		
		GwaMain *const main;
		const std::string name;
	};
	Application* createApplication();
}

