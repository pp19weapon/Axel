#include "axpch.h"
#include "Application.h"

#include "Axel/Log.h"

#include "GLFW/glfw3.h"

namespace Axel {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		AX_CORE_TRACE("{0}", e.toString());
	}
	bool Application::onWindowClose(WindowCloseEvent e)
	{
		m_running = false;
		return true;
	}
}
