#include "axpch.h"
#include "Renderer.h"

namespace Axel {

	void Renderer::beginScene()
	{
	}

	void Renderer::endScene()
	{
	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& t_vertexArray)
	{
		t_vertexArray->bind();
		RenderCommand::drawIndexed(t_vertexArray);
	}

}