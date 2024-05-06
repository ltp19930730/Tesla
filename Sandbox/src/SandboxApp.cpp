#include <tlpch.h>
#include <Tesla.h>


class ExampleLayer : public Tesla::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		TL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Tesla::Event& event) override
	{
		TL_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Tesla::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Tesla::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Tesla::Application* Tesla::CreateApplication()
{
	return new Sandbox();
}