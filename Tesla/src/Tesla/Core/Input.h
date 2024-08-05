#pragma once

#include "Tesla/Core/Base.h"
#include "Tesla/Core/KeyCodes.h"
#include "Tesla/Core/MouseCodes.h"
#include "tlpch.h"

namespace Tesla {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}