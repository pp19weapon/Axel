#include "axpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Axel {
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}