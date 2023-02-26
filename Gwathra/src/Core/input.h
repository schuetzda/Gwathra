#pragma once
#include <utility>

namespace gwa {
	class Input
	{
	
	public:
		static int IsKeyPressed(const int key);
		static int IsMouseButtonPressed(const int button);
		static std::pair<float, float> GetMousePosition();

	};
}