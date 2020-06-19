#include "axpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Axel {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_rendererID(0)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			AX_CORE_ERROR("{0}", infoLog.data());
			AX_CORE_ASSERT(false, "Vertex shader compilation failed!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			AX_CORE_ERROR("{0}", infoLog.data());
			AX_CORE_ASSERT(false, "Fragment shader compilation failed!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_rendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_rendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_rendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			AX_CORE_ERROR("{0}", infoLog.data());
			AX_CORE_ASSERT(false, "Shader linking failed!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_rendererID);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_rendererID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::uploadUniformMat4(const std::string& t_name, const glm::mat4& t_matrix) const
	{
		GLint location = getUniformLocation(t_name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}

	void OpenGLShader::uploadUniformMat3(const std::string& t_name, const glm::mat3& t_matrix) const
	{
		GLint location = getUniformLocation(t_name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(t_matrix));
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& t_name, const glm::vec4& t_values) const
	{
		GLint location = getUniformLocation(t_name);
		glUniform4f(location, t_values.x, t_values.y, t_values.z, t_values.w);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& t_name, const glm::vec3& t_values) const
	{
		GLint location = getUniformLocation(t_name);
		glUniform3f(location, t_values.x, t_values.y, t_values.z);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& t_name, const glm::vec2& t_values) const
	{
		GLint location = getUniformLocation(t_name);
		glUniform2f(location, t_values.x, t_values.y);
	}

	void OpenGLShader::uploadUniformFloat(const std::string& t_name, float t_value) const
	{
		GLint location = getUniformLocation(t_name);
		glUniform1f(location, t_value);
	}

	void OpenGLShader::uploadUniformInt(const std::string& t_name, int t_value) const
	{
		GLint location = getUniformLocation(t_name);
		glUniform1i(location, t_value);
	}

	int OpenGLShader::getUniformLocation(const std::string& t_name) const
	{
		auto locationSearch = m_uniformLocationCache.find(t_name);
		if (locationSearch != m_uniformLocationCache.end()){
			return locationSearch->second;
		}
		
		GLint location = glGetUniformLocation(m_rendererID, t_name.c_str());
		m_uniformLocationCache[t_name] = location;
		return location;
	}

}