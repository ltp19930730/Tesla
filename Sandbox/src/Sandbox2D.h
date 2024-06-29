#pragma once

#include "Tesla.h"

class Sandbox2D : public Tesla::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Tesla::Timestep ts, float time) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Tesla::Event& e) override;
private:
	Tesla::OrthographicCameraController m_CameraController;

	// Temp
	Tesla::Ref<Tesla::VertexArray> m_SquareVA;
	Tesla::Ref<Tesla::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

