#pragma once

#include "Axel/Renderer/VertexArray.h"

namespace Axel {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void addVertexBuffer(const ref<VertexBuffer>& t_vertexBuffer) override;
		virtual void setIndexBuffer(const ref<IndexBuffer>& t_indexBuffer) override;

		virtual const std::vector<ref<VertexBuffer>>& getVertexBuffers() const override{ return m_vertexBuffers; }
		virtual const ref<IndexBuffer>& getIndexBuffer() const override{ return m_indexBuffer; }
	private:
		uint32_t m_rendererID;
		std::vector<ref<VertexBuffer>> m_vertexBuffers;
		ref<IndexBuffer> m_indexBuffer;
	};
}