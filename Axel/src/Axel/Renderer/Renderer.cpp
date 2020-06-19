#include "axpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Axel {

	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData();

	void Renderer::beginScene(OrthographicCamera& t_camera)
	{
		m_sceneData->viewProjectionMatrix = t_camera.getViewProjectionMatrix();
	}

	void Renderer::endScene()
	{
	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& t_vertexArray, const std::shared_ptr<Shader>& t_shader, const glm::mat4& t_transform)
	{
		t_shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(t_shader)->uploadUniformMat4("u_ViewProjection", m_sceneData->viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(t_shader)->uploadUniformMat4("u_Transform", t_transform);

		t_vertexArray->bind();
		RenderCommand::drawIndexed(t_vertexArray);
	}

}