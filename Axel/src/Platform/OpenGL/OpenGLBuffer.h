#pragma once

#include "Axel/Renderer/Buffer.h"

namespace Axel {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;


		virtual void setLayout(const BufferLayout& layout) override { m_bufferLayout = layout; }
		virtual const BufferLayout& getLayout() const override { return m_bufferLayout; }

	private:
		uint32_t m_rendererID;
		BufferLayout m_bufferLayout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		uint32_t getCount() const override { return m_count; }

	private:
		uint32_t m_rendererID;
		uint32_t m_count;
	};
}