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

		m_vertexArray = Axel::ref<Axel::VertexArray>(Axel::VertexArray::create());

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Bottom-left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom-right
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // Top-right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // Top-left
		};

		m_vertexBuffer = Axel::ref<Axel::VertexBuffer>(Axel::VertexBuffer::create(vertices, sizeof(vertices)));
		Axel::BufferLayout layout = {
			{ Axel::ShaderDataType::Float3, "a_Position" },
			{ Axel::ShaderDataType::Float2, "a_TexCoord" }
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		m_vertexArray->setIndexBuffer(Axel::IndexBuffer::create(indices, 6));

		std::string flatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_flatColorShader = Axel::ref<Axel::Shader>(Axel::Shader::create(flatColorVertexSrc, flatColorFragmentSrc));

		std::string textureVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_textureShader = Axel::ref<Axel::Shader>(Axel::Shader::create(textureVertexSrc, textureFragmentSrc));

		m_texture = Axel::Texture2D::create("assets/textures/checkerboard.png");

		std::dynamic_pointer_cast<Axel::OpenGLShader>(m_textureShader)->bind();
		std::dynamic_pointer_cast<Axel::OpenGLShader>(m_textureShader)->uploadUniformInt("u_Texture", 0);
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

		std::dynamic_pointer_cast<Axel::OpenGLShader>(m_flatColorShader)->bind();
		std::dynamic_pointer_cast<Axel::OpenGLShader>(m_flatColorShader)->uploadUniformFloat3("u_Color", m_squareColor);

		for (int y = 0; y < 30; y++) {
			for (int x = 0; x < 30; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Axel::Renderer::submit(m_vertexArray, m_flatColorShader, transform);
			}
		}

		m_texture->bind();
		Axel::Renderer::submit(m_vertexArray, m_textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
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
	Axel::ref<Axel::Shader> m_flatColorShader, m_textureShader;

	Axel::ref<Axel::VertexArray> m_vertexArray;
	Axel::ref<Axel::VertexBuffer> m_vertexBuffer;

	Axel::ref<Axel::Texture2D> m_texture;

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