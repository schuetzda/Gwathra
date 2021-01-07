#include "Gwathra.h"

class SimpleCube : public gwa::GwaApp {
public:
	SimpleCube() {

	}

	~SimpleCube() {

	}
};

gwa::GwaApp* gwa::createApplication() {
	return new SimpleCube();
}
