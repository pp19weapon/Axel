#pragma once

#include <glm/glm.hpp>

namespace Axel {
	class OrthographicCamera{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() = default;

		void move(glm::vec3& t_direction);

		void setPosition(const glm::vec3& t_pos) { 
			m_position = t_pos;
			calculateViewMatrix();
		}

		const glm::vec3& getPosition() { return m_position; }

		void setRotation(float t_rotation) { 
			m_rotation = t_rotation;
			calculateViewMatrix();
		}

		float getRotation() const { return m_rotation; }

		const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

	private:
		void calculateViewMatrix();
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};
}