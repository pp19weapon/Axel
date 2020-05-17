#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Axel/Events/ApplicationEvent.h"


namespace Axel {

	class AXEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);
	private:
		bool onWindowClose(WindowCloseEvent e);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	Application* createApplication();

}

