#include "gwamain.h"

namespace gwa {
	GwaMain* GwaMain::instance;

	GwaMain* GwaMain::getInstance() {
		{
			if (GwaMain::instance == nullptr) {
				GwaMain::instance = new GwaMain();
			}
			return GwaMain::instance;
		}
	}


	void GwaMain::setInstance(GwaMain* main) {
		if (GwaMain::instance != nullptr) {
			delete GwaMain::instance;
		}

		GwaMain::instance = main;
	}
}