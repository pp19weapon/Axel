#pragma once

#include "RenderCommand.h"

namespace Axel {
	class Renderer {
	public:
		static void beginScene();
		static void endScene();
		static void submit(const std::shared_ptr<VertexArray>& t_vertexArray);


		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	};

}