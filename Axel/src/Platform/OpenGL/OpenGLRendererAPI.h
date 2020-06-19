#pragma once

#include "Axel/Renderer/RendererAPI.h"

namespace Axel {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI() {}
		~OpenGLRendererAPI() = default;

		virtual void setClearColor(const glm::vec4& t_color) override;
		virtual void clear() override;
		virtual void drawIndexed(const ref<VertexArray>& t_vertexArray) override;
	};

}