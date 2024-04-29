#include "Application.h"

#include "Tesla/Events/ApplicationEvent.h"
#include "Tesla/Events/KeyEvent.h"
#include "Tesla/Log.h"

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
		WindowResizeEvent e1(1280, 720);
		KeyPressedEvent e2(1, 1);

		if (e1.IsInCategory(EventCategoryApplication))
		{
			TL_TRACE(e1.ToString())
		}

		if (e2.IsInCategory(EventCategoryInput))
		{
			TL_WARN(e2.ToString())
		}

		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			TL_TRACE("Run game engine in 1 fps")
		}
	}
}