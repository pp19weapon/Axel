#include "axpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Axel {

	Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			AX_CORE_ASSERT(false, "None is currently not supported as a rendering API!\n Supported API(s): OpenGL");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);

		case RendererAPI::Direct3D:
			AX_CORE_ASSERT(false, "Direct3D is currently not supported as a rendering API!\n Supported API(s): OpenGL");
			return nullptr;

		case RendererAPI::Vulkan:
			AX_CORE_ASSERT(false, "Vulkan is currently not supported as a rendering API!\n Supported API(s): OpenGL");
			return nullptr;
		}

		AX_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

}