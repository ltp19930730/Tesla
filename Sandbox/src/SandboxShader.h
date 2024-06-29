#pragma once

#include "Tesla.h"

class SandboxShader : public Tesla::Layer
{
public:
	SandboxShader();
	virtual ~SandboxShader() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Tesla::Timestep ts, float time) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Tesla::Event& e) override;
private:
	Tesla::OrthographicCameraController m_CameraController;

	// Temp
	Tesla::Ref<Tesla::VertexArray> m_VertexArray;
	Tesla::Ref<Tesla::Shader> m_Shader;

	glm::vec3 m_Color1 = { 0.5f, 0.5f, 0.1f };
	glm::vec3 m_Color2 = { 0.5f, 0.0f, 0.5f };
};
