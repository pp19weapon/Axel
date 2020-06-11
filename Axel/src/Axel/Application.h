#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Axel/Events/ApplicationEvent.h"
#include "Axel/LayerStack.h"

#include "Axel/ImGui/ImGuiLayer.h"

namespace Axel {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline static Application& get() { return *s_instance; }
		inline Window& getWindow() { return *m_window; }
	private:
		bool onWindowClose(WindowCloseEvent e);

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_running = true;
		LayerStack m_layerStack;

	private:
		static Application* s_instance;
	};

	Application* createApplication();

}

