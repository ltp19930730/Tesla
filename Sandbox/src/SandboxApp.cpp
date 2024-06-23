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
		: Layer("Example"), m_CameraController(1.0f)
	{
		m_VertexArray.reset(Tesla::VertexArray::Create());

		Tesla::Ref<Tesla::VertexBuffer> vertexBuffer;

		// Create vertext buffer
		float vertices[] = {
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f
		};
		vertexBuffer.reset(Tesla::VertexBuffer::Create(vertices, sizeof(vertices)));

		Tesla::BufferLayout layout = {
			{ Tesla::ShaderDataType::Float3, "a_Position" },
			{ Tesla::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Create index buffer
		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0,  // Back face
			4, 5, 6, 6, 7, 4,  // Front face
			4, 5, 1, 1, 0, 4,  // Bottom face
			6, 7, 3, 3, 2, 6,  // Top face
			4, 7, 3, 3, 0, 4,  // Left face
			1, 5, 6, 6, 2, 1   // Right face
		};
		Tesla::Ref<Tesla::IndexBuffer> indexBuffer;
		indexBuffer.reset(Tesla::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Tesla::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Tesla::Ref<Tesla::VertexBuffer> squareVB;
		squareVB.reset(Tesla::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Tesla::ShaderDataType::Float3, "a_Position" },
			{ Tesla::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Tesla::Ref<Tesla::IndexBuffer> squareIB;
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

		m_Shader = Tesla::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);


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

		m_FlatColorShader = Tesla::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		m_Texture = Tesla::Texture2D::Create("assets/textures/corgi.png");
		m_BackgroundTexture = Tesla::Texture2D::Create("assets/textures/Checkerboard.png");

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	

		std::dynamic_pointer_cast<Tesla::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Tesla::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		m_RotationAngle += m_RotationSpeed * ts; // Update the rotation angle

		Tesla::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tesla::RenderCommand::Clear();

		Tesla::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationAngle), glm::vec3(0, 1, 0)); // Rotate around X-axis


		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		
		glm::vec3 center(0.0f, 0.0f, 0.0f); // Center of the heart shape

		for (int y = -20; y < 20; y++)
		{
			for (int x = -20; x < 20; x++)
			{
				float xf = x * 0.11f;
				float yf = y * 0.11f;

				if (isInHeartShape(xf, yf))
				{
					glm::vec3 pos(xf, yf, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), center) *
						rotation *
						glm::translate(glm::mat4(1.0f), -center + pos) * scale;
					// Adding background checkboard
					// m_BackgroundTexture->Bind();
					// Tesla::Renderer::Submit(m_TextureShader, m_SquareVA, transform);
					m_Texture->Bind();
					auto textureShader = m_ShaderLibrary.Get("Texture");
					Tesla::Renderer::Submit(textureShader, m_SquareVA, transform);
				}
			}
		}

		// Cube
		glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationAngle), glm::vec3(1, 1, 0)) * scale; // Rotate around an arbitrary axis
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->Bind();

		Tesla::Renderer::Submit(m_Shader, m_VertexArray, transform);

		Tesla::Renderer::EndScene();
	}

	virtual void OnEvent(Tesla::Event& e) override
	{
		m_CameraController.OnEvent(e);
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

	Tesla::ShaderLibrary m_ShaderLibrary;
	Tesla::Ref<Tesla::VertexArray> m_VertexArray;
	Tesla::Ref<Tesla::Shader> m_Shader;

	Tesla::Ref<Tesla::Shader> m_FlatColorShader;
	Tesla::Ref<Tesla::VertexArray> m_SquareVA;

	Tesla::Ref<Tesla::Texture2D> m_Texture, m_BackgroundTexture;

	Tesla::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.5f, 0.5f, 0.1f };

	float m_RotationAngle = 0.0f;
	float m_RotationSpeed = 40.0f;
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