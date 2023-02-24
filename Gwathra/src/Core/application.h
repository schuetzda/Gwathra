#pragma once
#include "GwaMain.h"
#include "camera.h"
#include <string>

int main(int argc, char** argv);

namespace gwa {
	class Application
	{
	public:
		Application(GwaMain *const main, const std::string& name);

		virtual ~Application();
		
		void init();
		void run();

		void* GetNativeWindow();
		static Application& Get() { return *s_Instance; }
		Camera& GetCam() { return cam; }

	private:
		void initGLFW();

		
		GwaMain *const main;
		const std::string name;
		Camera cam;

		static Application* s_Instance;
	};

	Application* createApplication();
}

