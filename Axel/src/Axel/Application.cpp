#include "axpch.h"
#include "Application.h"

#include "Axel/Log.h"

#include "Axel/Renderer/Renderer.h"


#include "Input.h"


namespace Axel {
	Application* Application::s_instance = nullptr;


	Application::Application()
	{
		AX_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(AX_BIND_EVENT_FN(Application::onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		m_vertexArray = std::shared_ptr<VertexArray>(VertexArray::create());
		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		m_vertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(m_vertexBuffer);
		
		uint32_t indices[3] = { 0, 1, 2 };

		m_indexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::create(indices, 3));
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

		m_shader = std::shared_ptr<Shader>(Shader::create(vertexSrc, fragmentSrc));
	}

	void Application::run()
	{
		while (m_running) {
			RenderCommand::setClearColor({ 0.2, 0.2, 0.2, 1 });
			RenderCommand::clear();

			Renderer::beginScene();
			
			m_shader->bind();
			Renderer::submit(m_vertexArray);
			
			Renderer::endScene();


			for (Layer* layer : m_layerStack) {
				layer->onUpdate();
			}

			m_ImGuiLayer->begin();
			for (Layer* layer : m_layerStack) {
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();


			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher eventDispatcher(e);
		eventDispatcher.dispatch<WindowCloseEvent>(AX_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); ) {
			(*--it)->onEvent(e);
			if (e.handled) {
				break;
			}
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
	}

	bool Application::onWindowClose(WindowCloseEvent e)
	{
		m_running = false;
		return true;
	}
}
