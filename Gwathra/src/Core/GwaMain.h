#pragma once

namespace gwa {
	class GwaMain
	{
	public:
		virtual void init();
		virtual void render();
		virtual void deactivate();
	};
}

