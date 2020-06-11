#include "Axel.h"

#include "imgui/imgui.h"
#include "Axel/Renderer/Renderer.h"
#include "Axel/Renderer/Shader.h"

class ExampleLayer : public Axel::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_vertexArray = std::shared_ptr<Axel::VertexArray>(Axel::VertexArray::create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		m_vertexBuffer = std::shared_ptr<Axel::VertexBuffer>(Axel::VertexBuffer::create(vertices, sizeof(vertices)));
		Axel::BufferLayout layout = {
			{ Axel::ShaderDataType::Float3, "a_Position" },
			{ Axel::ShaderDataType::Float4, "a_Color" }
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		m_indexBuffer = std::shared_ptr<Axel::IndexBuffer>(Axel::IndexBuffer::create(indices, 3));
		m_vertexArray->setIndexBuffer(m_indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_shader = std::shared_ptr<Axel::Shader>(Axel::Shader::create(vertexSrc, fragmentSrc));
	}

	virtual void onUpdate() override {
		Axel::RenderCommand::setClearColor({ 0.2, 0.2, 0.2, 1 });
		Axel::RenderCommand::clear();

		Axel::Renderer::beginScene();

		m_shader->bind();
		Axel::Renderer::submit(m_vertexArray);

		Axel::Renderer::endScene();
	}

	virtual void onImGuiRender() override {
		ImGui::Begin("TEST");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	virtual void onEvent(Axel::Event& event) override {
	}

private:
	std::shared_ptr<Axel::Shader> m_shader;
	std::shared_ptr<Axel::VertexArray> m_vertexArray;
	std::shared_ptr<Axel::VertexBuffer> m_vertexBuffer;
	std::shared_ptr<Axel::IndexBuffer> m_indexBuffer;
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