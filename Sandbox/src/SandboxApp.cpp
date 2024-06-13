#include <tlpch.h>
#include <Tesla.h>

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
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
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(Tesla::Shader::Create(vertexSrc, fragmentSrc));


		std::string flatColorShaderVertexSrc = R"(
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Tesla::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

	}

	virtual void OnUpdate(Tesla::Timestep ts) override
	{
		if (Tesla::Input::IsKeyPressed(TL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		if (Tesla::Input::IsKeyPressed(TL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Tesla::Input::IsKeyPressed(TL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Tesla::Input::IsKeyPressed(TL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Tesla::Input::IsKeyPressed(TL_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (Tesla::Input::IsKeyPressed(TL_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		if (Tesla::Input::IsKeyPressed(TL_KEY_Z))
			m_Camera.ZoomIn(m_ZoomAmount * ts);

		if (Tesla::Input::IsKeyPressed(TL_KEY_X))
			m_Camera.ZoomOut(m_ZoomAmount * ts);

		Tesla::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tesla::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Tesla::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = -20; y < 20; y++)
		{
			for (int x = -20; x < 20; x++)
			{
				float xf = x * 0.11f;
				float yf = y * 0.11f;

				if (isInHeartShape(xf, yf))
				{
					glm::vec3 pos(xf, yf, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Tesla::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		}

		//Tesla::Renderer::Submit(m_Shader, m_VertexArray);

		Tesla::Renderer::EndScene();
	}

	virtual void OnEvent(Tesla::Event& event) override
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:

	inline bool isInHeartShape(float x, float y)
	{
		float val = pow(x * x + y * y - 1, 3) - x * x * y * y * y;
		return val <= 0.0f;
	}

	std::shared_ptr<Tesla::VertexArray> m_VertexArray;
	std::shared_ptr<Tesla::Shader> m_Shader;

	std::shared_ptr<Tesla::Shader> m_FlatColorShader;
	std::shared_ptr<Tesla::VertexArray> m_SquareVA;

	Tesla::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
	float m_ZoomAmount = 1.0f;

	glm::vec3 m_SquareColor = { 0.5f, 0.5f, 0.1f };
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