#pragma once
#include "GwaMain.h"
#include <string>

int main(int argc, char** argv);

namespace gwa {
	class Application
	{
	public:
		Application(const std::string& name);
		void setMain(GwaMain* main);
		virtual ~Application();
		void run();

		static Application& GetInstance() { return *s_Instance; }
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);

	};
	Application* createApplication();
}

