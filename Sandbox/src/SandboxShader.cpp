#include "SandboxShader.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

SandboxShader::SandboxShader()
	: Layer("SandboxShader"), m_CameraController(1280.0f / 720.0f)
{
}

void SandboxShader::OnAttach()
{
	m_VertexArray = Tesla::VertexArray::Create();

	// Create vertext buffer
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f
	};
	Tesla::Ref<Tesla::VertexBuffer> vertexBuffer;
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

	// Shader
	m_Shader = Tesla::Shader::Create("assets/shaders/Magic.glsl");
}

void SandboxShader::OnDetach()
{
}

void SandboxShader::OnUpdate(Tesla::Timestep ts, float time)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Tesla::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Tesla::RenderCommand::Clear();

	Tesla::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat3("iResolution", glm::vec3(1280.0f, 720.0f, 1.0f));
	std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat("iTime", time);
	std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat3("color1", m_Color1);
	std::dynamic_pointer_cast<Tesla::OpenGLShader>(m_Shader)->UploadUniformFloat3("color2", m_Color2);

	Tesla::Renderer::Submit(m_Shader, m_VertexArray);

	Tesla::Renderer::EndScene();
}

void SandboxShader::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color1", glm::value_ptr(m_Color1));
	ImGui::ColorEdit3("Color2", glm::value_ptr(m_Color2));
	ImGui::End();
}


void SandboxShader::OnEvent(Tesla::Event& e)
{
	m_CameraController.OnEvent(e);
}