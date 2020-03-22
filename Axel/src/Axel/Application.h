#pragma once

#include "Core.h"

namespace Axel {

	class AXEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* CreateApplication();

}

