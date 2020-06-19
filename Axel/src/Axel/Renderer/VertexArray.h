#pragma once

#include <memory>
#include "Axel/Renderer/Buffer.h"

namespace Axel {
	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const ref<VertexBuffer>& t_vertexBuffer) = 0;
		virtual void setIndexBuffer(const ref<IndexBuffer>& t_indexBuffer) = 0;

		virtual const std::vector<ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const ref<IndexBuffer>& getIndexBuffer() const = 0;

		static VertexArray* create();
	};
}