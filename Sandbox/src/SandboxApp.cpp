#include <tlpch.h>
#include <Tesla.h>
#include "imgui/imgui.h"


class ExampleLayer : public Tesla::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
		if (Tesla::Input::IsKeyPressed(TL_KEY_TAB))
			TL_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnEvent(Tesla::Event& event) override
	{
		if (event.GetEventType() == Tesla::EventType::KeyPressed)
		{
			Tesla::KeyPressedEvent& e = (Tesla::KeyPressedEvent&)event;
			if (e.GetKeyCode() == TL_KEY_TAB)
				TL_TRACE("Tab key is pressed (event)!");
			TL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	virtual void OnImGuiRender() override
	{
	}
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