#include "Application.h"

#include "Axel/Events/ApplicationEvent.h"
#include "Axel/Log.h"

namespace Axel {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1200, 720);
		AX_TRACE(e.toString());

		while (true);
	}
}
