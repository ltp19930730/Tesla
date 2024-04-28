#pragma once

#ifdef TL_PLATFORM_WINDOWS

extern Tesla::Application* Tesla::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Tesla::CreateApplication();
	app->Run();
	delete app;
}

#endif