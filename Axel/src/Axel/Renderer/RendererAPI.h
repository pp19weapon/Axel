#pragma once

#include <glm/glm.hpp>

#include "Axel/Renderer/VertexArray.h"

namespace Axel {
	class RendererAPI {
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1,
			Direct3D = 2,
			Vulkan = 3
		};
	public:
		virtual void setClearColor(const glm::vec4& t_color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& t_vertexArray) = 0;

		inline static API getAPI() { return s_api; }
	private:
		static API s_api;
	};
}