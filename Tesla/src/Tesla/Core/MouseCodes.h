#pragma once

namespace Tesla
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define TL_MOUSE_BUTTON_0      ::Tesla::Mouse::Button0
#define TL_MOUSE_BUTTON_1      ::Tesla::Mouse::Button1
#define TL_MOUSE_BUTTON_2      ::Tesla::Mouse::Button2
#define TL_MOUSE_BUTTON_3      ::Tesla::Mouse::Button3
#define TL_MOUSE_BUTTON_4      ::Tesla::Mouse::Button4
#define TL_MOUSE_BUTTON_5      ::Tesla::Mouse::Button5
#define TL_MOUSE_BUTTON_6      ::Tesla::Mouse::Button6
#define TL_MOUSE_BUTTON_7      ::Tesla::Mouse::Button7
#define TL_MOUSE_BUTTON_LAST   ::Tesla::Mouse::ButtonLast
#define TL_MOUSE_BUTTON_LEFT   ::Tesla::Mouse::ButtonLeft
#define TL_MOUSE_BUTTON_RIGHT  ::Tesla::Mouse::ButtonRight
#define TL_MOUSE_BUTTON_MIDDLE ::Tesla::Mouse::ButtonMiddle