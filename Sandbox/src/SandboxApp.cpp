#include "Axel.h"

#include "imgui/imgui.h"

class ExampleLayer : public Axel::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{}

	virtual void onUpdate() override {
		if (Axel::Input::isKeyPressed(AX_KEY_A)) {
			AX_INFO("WOW");
		}
	}

	virtual void onImGuiRender() override {
		ImGui::Begin("TEST");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	virtual void onEvent(Axel::Event& event) override {
		AX_TRACE("{0}", event.toString());
	}
};

class Sandbox : public Axel::Application {
public:
	Sandbox() 
	{
		pushLayer(new ExampleLayer());
	}
	
	~Sandbox()
	{

	}
};

Axel::Application* Axel::createApplication() {
	return new Sandbox();
}