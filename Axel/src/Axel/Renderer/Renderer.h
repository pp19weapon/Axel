#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Axel {
	class Renderer {
	public:
		static void beginScene(OrthographicCamera& t_camera);
		static void endScene();
		static void submit(const ref<VertexArray>& t_vertexArray, const ref<Shader>& t_shader, const glm::mat4& t_transform = glm::mat4(1.0f));


		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* m_sceneData;
	};

}