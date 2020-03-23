#include "Axel.h"

class Sandbox : public Axel::Application {
public:
	Sandbox() 
	{

	}

	~Sandbox()
	{

	}
};

Axel::Application* Axel::createApplication() {
	return new Sandbox();
}