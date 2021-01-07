#pragma once
#include "GwaApp.h"
#ifdef GWA_PLATFORM_WINDOWS

	extern gwa::GwaApp* gwa::createApplication();

	int main(int argc, char** argv) {
		auto app = gwa::createApplication();
		app->run();
		delete app;
	}


#endif