#pragma once

#include "Axel/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Axel {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		void uploadUniformMat4(const std::string& t_name, const glm::mat4& t_matrix) const;
		void uploadUniformMat3(const std::string& t_name, const glm::mat3& t_matrix) const;

		void uploadUniformFloat4(const std::string& t_name, const glm::vec4& t_values) const;
		void uploadUniformFloat3(const std::string& t_name, const glm::vec3& t_values) const;
		void uploadUniformFloat2(const std::string& t_name, const glm::vec2& t_values) const;
		void uploadUniformFloat(const std::string& t_name, float t_value) const;

		void uploadUniformInt(const std::string& t_name, int t_value) const;

	private:
		uint32_t m_rendererID;
	};
}