#include "Gwathra.h"
#include "raymain.h"
#include "Core/entrypoint.h"
namespace gwa {
	class SimpleCube : public Application {

	public:
		SimpleCube() : Application(new RayMain(), "RayTracer") {

		}
		~SimpleCube() {

		}
	};
	Application* createApplication() {
		return new SimpleCube();
	}
}