#pragma once
#include <tuple>

namespace gwa {
	class Input
	{
	
	public:
		static int IsKeyPressed(const int key);
		static int IsMouseButtonPressed(const int button);
		static std::tuple<float, float> GetMousePosition();

	};
}