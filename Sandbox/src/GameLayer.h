#pragma once

#include "Tesla.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Tesla::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Tesla::Timestep ts, float time) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Tesla::Event& e) override;
	bool OnMouseButtonPressed(Tesla::MouseButtonPressedEvent& e);
	bool OnWindowResize(Tesla::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Tesla::Scope<Tesla::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};
