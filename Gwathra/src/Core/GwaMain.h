#pragma once

namespace gwa {
	class GwaMain
	{
	public:
		virtual ~GwaMain() {
			delete& instance;
		}

		static GwaMain* getInstance();

		static void setInstance(GwaMain* main);


		virtual void init() {}
		virtual void render() {}
		virtual void deactivate() {}

		virtual void windowSizeChanged(int width, int height) {}
	private:
		static GwaMain* instance;
	};
}