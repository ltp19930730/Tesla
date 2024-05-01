#include "tlpch.h"
#include "Application.h"

#include "Tesla/Events/ApplicationEvent.h"
#include "Tesla/Events/KeyEvent.h"
#include "Tesla/Log.h"

#include <GLFW/glfw3.h>

namespace Tesla {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
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

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}