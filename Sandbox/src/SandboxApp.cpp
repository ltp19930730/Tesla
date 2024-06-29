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
		: Layer("Example"), m_CameraController(1.0f, true)
	{
		m_VertexArray.reset(Tesla::VertexArray::Create());

		Tesla::Ref<Tesla::VertexBuffer> vertexBuffer;

		// Create vertext buffer
		float vertices[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
		};
		vertexBuffer.reset(Tesla::VertexBuffer::Create(vertices, sizeof(vertices)));

		Tesla::BufferLayout layout = {
			{ Tesla::ShaderDataType::Float3, "a_Position" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Create index buffer
		uint32_t indices[] = {
			0, 1, 2,
			2, 3, 0
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

		m_Shader = m_ShaderLibrary.Load("assets/shaders/Magic.glsl");

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

	virtual void OnUpdate(Tesla::Timestep ts, float time) override
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
		//std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		
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
		

		/*
		* Custom shader playground
		*/
		/*
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat3("iResolution", glm::vec3(1280.0f, 720.0f, 1.0f));
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat("iTime", time);
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat3("color1", m_Color1);
		std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat3("color2", m_Color2);

		Tesla::Renderer::Submit(m_Shader, m_VertexArray);
		*/

		Tesla::Renderer::EndScene();
	}

	virtual void OnEvent(Tesla::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color1", glm::value_ptr(m_Color1));
		ImGui::ColorEdit3("Color2", glm::value_ptr(m_Color2));
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

	glm::vec3 m_Color1 = { 0.5f, 0.5f, 0.1f };

	glm::vec3 m_Color2 = { 0.5f, 0.0f, 0.5f };

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