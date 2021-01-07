#pragma once

#include "GwaCore.h"
namespace gwa {
	class GWA_API GwaApp
	{
	public:
		GwaApp();
		virtual ~GwaApp();
		void run();
	};

	GwaApp* createApplication();
}

