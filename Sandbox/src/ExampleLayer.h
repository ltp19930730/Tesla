#pragma once

#include "Tesla.h"

class ExampleLayer : public Tesla::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Tesla::Timestep ts, float time) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Tesla::Event& e) override;

private:
	inline bool isInHeartShape(float x, float y)
	{
		float val = pow(x * x + y * y - 1, 3) - x * x * y * y * y;
		return val <= 0.0f;
	}

	Tesla::ShaderLibrary m_ShaderLibrary;

	Tesla::Ref<Tesla::Shader> m_FlatColorShader;
	Tesla::Ref<Tesla::VertexArray> m_SquareVA;

	Tesla::Ref<Tesla::Texture2D> m_Texture, m_BackgroundTexture;

	Tesla::OrthographicCameraController m_CameraController;

	glm::vec3 m_Color1 = { 0.5f, 0.5f, 0.1f };

	glm::vec3 m_Color2 = { 0.5f, 0.0f, 0.5f };

	float m_RotationAngle = 0.0f;
	float m_RotationSpeed = 40.0f;
};