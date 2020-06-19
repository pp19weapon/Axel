#include "axpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Axel {

	void OpenGLRendererAPI::setClearColor(const glm::vec4& t_color)
	{
		glClearColor(t_color.r, t_color.g, t_color.b, t_color.a);
	}

	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::drawIndexed(const ref<VertexArray>& t_vertexArray)
	{
		glDrawElements(GL_TRIANGLES, t_vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}