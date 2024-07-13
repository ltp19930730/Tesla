#pragma once

#include "Tesla/Core/Core.h"

#ifdef TL_PLATFORM_WINDOWS

extern Tesla::Application* Tesla::CreateApplication();

int main(int argc, char** argv)
{
	Tesla::Log::init();

	TL_PROFILE_BEGIN_SESSION("Startup", "TeslaProfile-Startup.json");
	auto app = Tesla::CreateApplication();
	TL_PROFILE_END_SESSION();

	TL_PROFILE_BEGIN_SESSION("Runtime", "TeslaProfile-Runtime.json");
	app->Run();
	TL_PROFILE_END_SESSION();

	TL_PROFILE_BEGIN_SESSION("Shutdown", "TeslaProfile-Shutdown.json");
	delete app;
	TL_PROFILE_END_SESSION();
}

#endif