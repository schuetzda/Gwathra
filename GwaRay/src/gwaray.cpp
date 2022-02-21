#include "Gwathra.h"
#include "raymain.h"
#include "Core/entrypoint.h"

namespace gwa {
	class GwaRay : public Application {

	public:
		GwaRay() : Application(new RayMain(), "RayTracerino") {

		}
		~GwaRay() {

		}
	};
	Application* createApplication() {
		return new GwaRay();
	}
}