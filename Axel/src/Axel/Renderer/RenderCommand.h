#pragma once

#include "RendererAPI.h"

namespace Axel {
	class RenderCommand {
	public:
		inline static void setClearColor(const glm::vec4& t_color) {
			s_rendererAPI->setClearColor(t_color);
		}

		inline static void clear() {
			s_rendererAPI->clear();
		}

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& t_vertexArray) {
			s_rendererAPI->drawIndexed(t_vertexArray);
		}
	private:
		static RendererAPI* s_rendererAPI;
	};
}