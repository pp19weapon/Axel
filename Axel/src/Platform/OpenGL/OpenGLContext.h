#pragma once

#include "Axel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Axel {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}