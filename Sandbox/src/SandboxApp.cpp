#include "Axel.h"

class ExampleLayer : public Axel::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void onUpdate() override {
		AX_INFO("Example Layer onUpdate test");
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