#pragma once

namespace Axel {
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		Direct3D = 2,
		Vulkan = 3
	};

	class Renderer {
	public:
		inline static RendererAPI getAPI() { return s_rendererAPI; }
	private:
		static RendererAPI s_rendererAPI;
	};

}