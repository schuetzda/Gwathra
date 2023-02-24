#pragma once
#include <tuple>

namespace gwa {
	class Input
	{
	
	public:
		static bool IsKeyPressed(const int key);
		static bool IsMouseButtonPressed(const int button);
		static std::tuple<float, float> GetMousePosition();

	};
}