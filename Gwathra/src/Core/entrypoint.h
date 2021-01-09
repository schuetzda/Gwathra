#pragma once
#include "Application.h"
#ifdef GWA_PLATFORM_WINDOWS

	extern gwa::Application* gwa::createApplication();

	int main(int argc, char** argv) {
		auto app = gwa::createApplication();
		app->run();
		delete app;
	}


#endif