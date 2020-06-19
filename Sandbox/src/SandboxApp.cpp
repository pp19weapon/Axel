#include "Axel.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Axel/Utils/FPSCounter.h"

class ExampleLayer : public Axel::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_position(0.0f)

	{
		Axel::FPSCounter::init(60);

		m_vertexArray = std::shared_ptr<Axel::VertexArray>(Axel::VertexArray::create());

		float vertices[4 * 3] = {
			-0.5f,  0.5f, 1.0f, // Top-left
			 0.5f,  0.5f, 0.0f, // Top-right
			 0.5f, -0.5f, 0.0f, // Bottom-right
			-0.5f, -0.5f, 1.0f, // Bottom-left
		};

		m_vertexBuffer = std::shared_ptr<Axel::VertexBuffer>(Axel::VertexBuffer::create(vertices, sizeof(vertices)));
		Axel::BufferLayout layout = {
			{ Axel::ShaderDataType::Float3, "a_Position" }
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		m_indexBuffer = std::shared_ptr<Axel::IndexBuffer>(Axel::IndexBuffer::create(indices, 6));
		m_vertexArray->setIndexBuffer(m_indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_squareShader = std::shared_ptr<Axel::Shader>(Axel::Shader::create(vertexSrc, fragmentSrc));
	}

	virtual void onUpdate(Axel::Timestep ts) override {
		glm::vec3 cameraMoveDirection;
		glm::float32 cameraSpeed = 1.0f;
		float objSpeed = 1.0f;

		//Camera controls
		if (Axel::Input::isKeyPressed(AX_KEY_W)) {
			cameraMoveDirection = glm::vec3(0.0f, -1.0f, 0.0f);
			m_camera.setPosition(m_camera.getPosition() - (cameraMoveDirection * (cameraSpeed * ts)));
		}
		else if (Axel::Input::isKeyPressed(AX_KEY_S)) {
			cameraMoveDirection = glm::vec3(0.0f, 1.0f, 0.0f);
			m_camera.setPosition(m_camera.getPosition() - (cameraMoveDirection * (cameraSpeed * ts)));
		}

		if (Axel::Input::isKeyPressed(AX_KEY_A)) {
			cameraMoveDirection = glm::vec3(1.0f, 0.0f, 0.0f);
			m_camera.setPosition(m_camera.getPosition() - (cameraMoveDirection * (cameraSpeed * ts)));
		}
		else if (Axel::Input::isKeyPressed(AX_KEY_D)) {
			cameraMoveDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
			m_camera.setPosition(m_camera.getPosition() - (cameraMoveDirection * (cameraSpeed * ts)));
		}

		Axel::RenderCommand::setClearColor({ 0.2, 0.2, 0.2, 1 });
		Axel::RenderCommand::clear();

		Axel::Renderer::beginScene(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Axel::OpenGLShader>(m_squareShader)->bind();
		std::dynamic_pointer_cast<Axel::OpenGLShader>(m_squareShader)->uploadUniformFloat3("u_Color", m_squareColor);

		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Axel::Renderer::submit(m_vertexArray, m_squareShader, transform);
			}
		}

		
		Axel::Renderer::endScene();

		Axel::FPSCounter::addNewFPSValue(1 / ts);
	}

	virtual void onImGuiRender() override {
		ImGui::Begin("FPS");
		ImGui::Text(std::to_string(int(Axel::FPSCounter::getFPS())).c_str());
		ImGui::End();

		ImGui::Begin("Square Color");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_squareColor));
		ImGui::End();
	}

	virtual void onEvent(Axel::Event& event) override {
	}

private:
	std::shared_ptr<Axel::Shader> m_squareShader;
	std::shared_ptr<Axel::VertexArray> m_vertexArray;
	std::shared_ptr<Axel::VertexBuffer> m_vertexBuffer;
	std::shared_ptr<Axel::IndexBuffer> m_indexBuffer;
	Axel::OrthographicCamera m_camera;

	glm::vec3 m_position;
	glm::vec3 m_squareColor = { 0.2f, 0.3f, 0.8f };
	int m_fps = 0;
};

class Sandbox : public Axel::Application {
public:
	Sandbox() 
	{
		pushLayer(new ExampleLayer());
	}
	
	~Sandbox()
	{

	}
};

Axel::Application* Axel::createApplication() {
	return new Sandbox();
}