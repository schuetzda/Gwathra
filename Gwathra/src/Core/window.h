#pragma once
#include <stdint.h>

namespace gwa {
	class Window
	{
	public:
		Window(const char* title, const uint32_t width = 1920, const uint32_t height = 1080);
		~Window();

		void update();
		
	private:
		const char* title;
		const unsigned int width, height;

		void initWindow();
	};
}

