#include "Gwathra.h"
#include "cubemain.h"
#include "Core/entrypoint.h"
namespace gwa {
	class SimpleCube : public Application {

	public:
		SimpleCube() : Application("SimpleCube"){
			setMain(new CubeMain());
		}
		~SimpleCube() {

		}
	};
	Application* createApplication() {
		return new SimpleCube();
	}
}