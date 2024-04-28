#include <Tesla.h>


class Sandbox : public Tesla::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Tesla::Application* Tesla::CreateApplication()
{
	return new Sandbox();
}