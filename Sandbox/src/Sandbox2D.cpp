#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	TL_PROFILE_FUNCTION();

	m_CheckerboardTexture = Tesla::Texture2D::Create("assets/textures/Checkerboard.png");

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 30.0f);
}

void Sandbox2D::OnDetach()
{
	TL_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Tesla::Timestep ts, float time)
{
	TL_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(ts);


	// Render
	Tesla::Renderer2D::ResetStats();
	{
		TL_PROFILE_SCOPE("Renderer Prep");
		Tesla::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tesla::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		TL_PROFILE_SCOPE("Renderer Draw");
		Tesla::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Tesla::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, rotation,{ 0.8f, 0.2f, 0.3f, 1.0f });
		Tesla::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Tesla::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Tesla::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Tesla::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Tesla::Renderer2D::EndScene();


		Tesla::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Tesla::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Tesla::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	TL_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	auto stats = Tesla::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}


void Sandbox2D::OnEvent(Tesla::Event& e)
{
	TL_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}