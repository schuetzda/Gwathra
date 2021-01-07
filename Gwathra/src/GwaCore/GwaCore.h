#pragma once

#ifdef GWA_PLATFORM_WINDOWS
	#ifdef GWA_BUILD_DLL
		#define GWA_API __declspec(dllexport)
	#else
		#define GWA_API __declspec(dllimport)
	#endif
#else
	#error Gwa supports only windows
#endif