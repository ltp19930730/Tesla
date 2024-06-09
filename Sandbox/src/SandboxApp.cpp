#include <tlpch.h>
#include <Tesla.h>

#include "imgui/imgui.h"


class ExampleLayer : public Tesla::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Tesla::VertexArray::Create());

		std::shared_ptr<Tesla::VertexBuffer> vertexBuffer;

		// Create vertext buffer
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		vertexBuffer.reset(Tesla::VertexBuffer::Create(vertices, sizeof(vertices)));

		Tesla::BufferLayout layout = {
			{ Tesla::ShaderDataType::Float3, "a_Position" },
			{ Tesla::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Create index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Tesla::IndexBuffer> indexBuffer;
		indexBuffer.reset(Tesla::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Tesla::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Tesla::VertexBuffer> squareVB;
		squareVB.reset(Tesla::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Tesla::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Tesla::IndexBuffer> squareIB;
		squareIB.reset(Tesla::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Tesla::Shader(vertexSrc, fragmentSrc));


		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Tesla::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}

	virtual void OnUpdate() override
	{
		if (Tesla::Input::IsKeyPressed(TL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;

		if (Tesla::Input::IsKeyPressed(TL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Tesla::Input::IsKeyPressed(TL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Tesla::Input::IsKeyPressed(TL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Tesla::Input::IsKeyPressed(TL_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed;

		if (Tesla::Input::IsKeyPressed(TL_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed;

		Tesla::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tesla::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Tesla::Renderer::BeginScene(m_Camera);

		Tesla::Renderer::Submit(m_BlueShader, m_SquareVA);
		Tesla::Renderer::Submit(m_Shader, m_VertexArray);

		Tesla::Renderer::EndScene();
	}

	virtual void OnEvent(Tesla::Event& event) override
	{
	}

	virtual void OnImGuiRender() override
	{
	}

private:
	std::shared_ptr<Tesla::VertexArray> m_VertexArray;
	std::shared_ptr<Tesla::Shader> m_Shader;

	std::shared_ptr<Tesla::Shader> m_BlueShader;
	std::shared_ptr<Tesla::VertexArray> m_SquareVA;

	Tesla::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Tesla::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Tesla::Application* Tesla::CreateApplication()
{
	return new Sandbox();
}