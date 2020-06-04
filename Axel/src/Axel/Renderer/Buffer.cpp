#include "axpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Axel {
	VertexBuffer* VertexBuffer::create(float* verticies, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			AX_CORE_ASSERT(false, "None is currently not supported as a rendering API!\n Supported API(s): OpenGL");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(verticies, size);

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
	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			AX_CORE_ASSERT(false, "None is currently not supported as a rendering API!\n Supported API(s): OpenGL");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

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