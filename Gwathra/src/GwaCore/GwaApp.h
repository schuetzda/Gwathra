#pragma once

#include "GwaCore.h"
namespace gwa {
	class GwaApp
	{
	public:
		GwaApp();
		virtual ~GwaApp();
		void run();
	};

	GwaApp* createApplication();
}

