#include "tlpch.h"
#include "Tesla/Core/Input.h"

#ifdef TL_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Tesla {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef TL_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		TL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}