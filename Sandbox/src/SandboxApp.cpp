#include <tlpch.h>
#include <Tesla.h>
#include <Tesla/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "SandboxShader.h"
#include "ExampleLayer.h"
#include "GameLayer.h"


class Sandbox : public Tesla::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		//PushLayer(new SandboxShader());
		//PushLayer(new Sandbox2D());
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{

	}
};

Tesla::Application* Tesla::CreateApplication()
{
	return new Sandbox();
}