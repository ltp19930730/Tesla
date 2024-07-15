#include <tlpch.h>
#include <Tesla.h>
#include <Tesla/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "SandboxShader.h"
#include "ExampleLayer.h"


class Sandbox : public Tesla::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		//PushLayer(new SandboxShader());
	}

	~Sandbox()
	{

	}
};

Tesla::Application* Tesla::CreateApplication()
{
	return new Sandbox();
}