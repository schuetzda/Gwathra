#include "Gwathra.h"
#include "cubemain.h"
#include "Core/entrypoint.h"
namespace gwa {
	class SimpleCube : public Application {

	public:
		SimpleCube() : Application(new CubeMain(),"SimpleCube"){

		}
		~SimpleCube() {

		}
	};
	Application* createApplication() {
		return new SimpleCube();
	}
}