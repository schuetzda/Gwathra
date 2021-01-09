#include "Gwathra.h"

class SimpleCube : public gwa::Application {

public:
	SimpleCube() {
		
	}
	~SimpleCube() {

	}
};
gwa::Application* gwa::createApplication() {
	return new SimpleCube();
}
