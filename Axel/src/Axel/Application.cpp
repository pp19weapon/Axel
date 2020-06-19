#include "axpch.h"
#include "Application.h"

#include "Axel/Log.h"

#include "Input.h"

#include <GLFW/glfw3.h>


namespace Axel {
	Application* Application::s_instance = nullptr;


	Application::Application()
	{
		AX_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(AX_BIND_EVENT_FN(Application::onEvent));
		m_window->setVSync(true);

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		
	}

	void Application::run()
	{
		while (m_running) {
			float time = (float)glfwGetTime();		//TODO: Make platform specific Platform::GetTime()
			Timestep timestep = time - m_lastFrameTime;
			m_lastFrameTime = time;

			for (Layer* layer : m_layerStack) {
				layer->onUpdate(timestep);
			}

			m_ImGuiLayer->begin();
			for (Layer* layer : m_layerStack) {
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();


			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(AX_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); ) {
			(*--it)->onEvent(e);
			if (e.handled) {
				break;
			}
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
	}

	bool Application::onWindowClose(WindowCloseEvent e)
	{
		m_running = false;
		return true;
	}
}
