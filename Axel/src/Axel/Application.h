#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Axel/Events/ApplicationEvent.h"
#include "Axel/LayerStack.h"

#include "Axel/ImGui/ImGuiLayer.h"

#include "Axel/Renderer/Shader.h"
#include "Axel/Renderer/Buffer.h"
#include "Axel/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	private:
		static Application* s_instance;
	};

	Application* createApplication();

}

