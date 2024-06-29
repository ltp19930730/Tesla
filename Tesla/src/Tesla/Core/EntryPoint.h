#pragma once

#ifdef TL_PLATFORM_WINDOWS

extern Tesla::Application* Tesla::CreateApplication();

int main(int argc, char** argv)
{
	Tesla::Log::init();

	TL_CORE_ERROR("Game engine starts!");

	int var = 5;

	TL_INFO("Client engine var ={0}", var);

	auto app = Tesla::CreateApplication();
	app->Run();
	delete app;
}

#endif