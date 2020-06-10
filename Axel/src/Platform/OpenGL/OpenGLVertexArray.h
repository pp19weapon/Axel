#pragma once

#include "Axel/Renderer/VertexArray.h"

namespace Axel {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& t_vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& t_indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override{ return m_vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override{ return m_indexBuffer; }
	private:
		uint32_t m_rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	};
}