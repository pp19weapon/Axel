#include "Axel.h"

class ExampleLayer : public Axel::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void onUpdate() override {
		if (Axel::Input::isKeyPressed(AX_KEY_A)) {
			AX_INFO("WOW");
		}
	}

	void onEvent(Axel::Event& event) override {
		AX_TRACE("{0}", event.toString());
	}
};

class Sandbox : public Axel::Application {
public:
	Sandbox() 
	{
		pushLayer(new ExampleLayer());
		pushOverlay(new Axel::ImGuiLayer());
	}
	
	~Sandbox()
	{

	}
};

Axel::Application* Axel::createApplication() {
	return new Sandbox();
}