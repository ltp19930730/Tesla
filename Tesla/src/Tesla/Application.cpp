#include "Application.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace Tesla {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "Run game engine in 1 fps" << std::endl;
		}
	}
}