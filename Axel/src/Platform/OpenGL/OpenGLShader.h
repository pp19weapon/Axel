#pragma once

#include "Axel/Renderer/Shader.h"

namespace Axel {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		void bind() const override;
		void unbind() const override;

	private:
		uint32_t m_rendererID;
	};
}