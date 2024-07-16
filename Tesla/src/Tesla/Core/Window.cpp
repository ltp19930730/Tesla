#include "tlpch.h"
#include "Tesla/Core/Window.h"

#ifdef TL_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Tesla
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef TL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		TL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}