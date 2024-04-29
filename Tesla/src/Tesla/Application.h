#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Tesla {
	class TL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

