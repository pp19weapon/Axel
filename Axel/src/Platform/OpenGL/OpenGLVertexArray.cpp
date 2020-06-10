#include "axpch.h"

#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Axel {

	static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType t_type) {
		switch (t_type)
		{
		case Axel::ShaderDataType::None:		return GL_FLOAT;
		case Axel::ShaderDataType::Float:		return GL_FLOAT;
		case Axel::ShaderDataType::Float2:		return GL_FLOAT;
		case Axel::ShaderDataType::Float3:		return GL_FLOAT;
		case Axel::ShaderDataType::Float4:		return GL_FLOAT;
		case Axel::ShaderDataType::Mat3:		return GL_FLOAT;
		case Axel::ShaderDataType::Mat4:		return GL_FLOAT;
		case Axel::ShaderDataType::Int:			return GL_INT;
		case Axel::ShaderDataType::Int2:		return GL_INT;
		case Axel::ShaderDataType::Int3:		return GL_INT;
		case Axel::ShaderDataType::Int4:		return GL_INT;
		case Axel::ShaderDataType::Bool:		return GL_BOOL;
		}

		AX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& t_vertexBuffer)
	{
		AX_CORE_ASSERT(t_vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_rendererID);
		t_vertexBuffer->bind();


		uint32_t index = 0;
		const auto& layout = t_vertexBuffer->getLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.getComponentCount(),
				shaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset
			);
			index++;
		}
		m_vertexBuffers.push_back(t_vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& t_indexBuffer)
	{
		glBindVertexArray(m_rendererID);
		t_indexBuffer->bind();

		m_indexBuffer = t_indexBuffer;
	}

}