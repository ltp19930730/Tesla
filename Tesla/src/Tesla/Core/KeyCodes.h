#pragma once
namespace Tesla
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define TL_KEY_SPACE           ::Tesla::Key::Space
#define TL_KEY_APOSTROPHE      ::Tesla::Key::Apostrophe    /* ' */
#define TL_KEY_COMMA           ::Tesla::Key::Comma         /* , */
#define TL_KEY_MINUS           ::Tesla::Key::Minus         /* - */
#define TL_KEY_PERIOD          ::Tesla::Key::Period        /* . */
#define TL_KEY_SLASH           ::Tesla::Key::Slash         /* / */
#define TL_KEY_0               ::Tesla::Key::D0
#define TL_KEY_1               ::Tesla::Key::D1
#define TL_KEY_2               ::Tesla::Key::D2
#define TL_KEY_3               ::Tesla::Key::D3
#define TL_KEY_4               ::Tesla::Key::D4
#define TL_KEY_5               ::Tesla::Key::D5
#define TL_KEY_6               ::Tesla::Key::D6
#define TL_KEY_7               ::Tesla::Key::D7
#define TL_KEY_8               ::Tesla::Key::D8
#define TL_KEY_9               ::Tesla::Key::D9
#define TL_KEY_SEMICOLON       ::Tesla::Key::Semicolon     /* ; */
#define TL_KEY_EQUAL           ::Tesla::Key::Equal         /* = */
#define TL_KEY_A               ::Tesla::Key::A
#define TL_KEY_B               ::Tesla::Key::B
#define TL_KEY_C               ::Tesla::Key::C
#define TL_KEY_D               ::Tesla::Key::D
#define TL_KEY_E               ::Tesla::Key::E
#define TL_KEY_F               ::Tesla::Key::F
#define TL_KEY_G               ::Tesla::Key::G
#define TL_KEY_H               ::Tesla::Key::H
#define TL_KEY_I               ::Tesla::Key::I
#define TL_KEY_J               ::Tesla::Key::J
#define TL_KEY_K               ::Tesla::Key::K
#define TL_KEY_L               ::Tesla::Key::L
#define TL_KEY_M               ::Tesla::Key::M
#define TL_KEY_N               ::Tesla::Key::N
#define TL_KEY_O               ::Tesla::Key::O
#define TL_KEY_P               ::Tesla::Key::P
#define TL_KEY_Q               ::Tesla::Key::Q
#define TL_KEY_R               ::Tesla::Key::R
#define TL_KEY_S               ::Tesla::Key::S
#define TL_KEY_T               ::Tesla::Key::T
#define TL_KEY_U               ::Tesla::Key::U
#define TL_KEY_V               ::Tesla::Key::V
#define TL_KEY_W               ::Tesla::Key::W
#define TL_KEY_X               ::Tesla::Key::X
#define TL_KEY_Y               ::Tesla::Key::Y
#define TL_KEY_Z               ::Tesla::Key::Z
#define TL_KEY_LEFT_BRACKET    ::Tesla::Key::LeftBracket   /* [ */
#define TL_KEY_BACKSLASH       ::Tesla::Key::Backslash     /* \ */
#define TL_KEY_RIGHT_BRACKET   ::Tesla::Key::RightBracket  /* ] */
#define TL_KEY_GRAVE_ACCENT    ::Tesla::Key::GraveAccent   /* ` */
#define TL_KEY_WORLD_1         ::Tesla::Key::World1        /* non-US #1 */
#define TL_KEY_WORLD_2         ::Tesla::Key::World2        /* non-US #2 */

/* Function keys */
#define TL_KEY_ESCAPE          ::Tesla::Key::Escape
#define TL_KEY_ENTER           ::Tesla::Key::Enter
#define TL_KEY_TAB             ::Tesla::Key::Tab
#define TL_KEY_BACKSPACE       ::Tesla::Key::Backspace
#define TL_KEY_INSERT          ::Tesla::Key::Insert
#define TL_KEY_DELETE          ::Tesla::Key::Delete
#define TL_KEY_RIGHT           ::Tesla::Key::Right
#define TL_KEY_LEFT            ::Tesla::Key::Left
#define TL_KEY_DOWN            ::Tesla::Key::Down
#define TL_KEY_UP              ::Tesla::Key::Up
#define TL_KEY_PAGE_UP         ::Tesla::Key::PageUp
#define TL_KEY_PAGE_DOWN       ::Tesla::Key::PageDown
#define TL_KEY_HOME            ::Tesla::Key::Home
#define TL_KEY_END             ::Tesla::Key::End
#define TL_KEY_CAPS_LOCK       ::Tesla::Key::CapsLock
#define TL_KEY_SCROLL_LOCK     ::Tesla::Key::ScrollLock
#define TL_KEY_NUM_LOCK        ::Tesla::Key::NumLock
#define TL_KEY_PRINT_SCREEN    ::Tesla::Key::PrintScreen
#define TL_KEY_PAUSE           ::Tesla::Key::Pause
#define TL_KEY_F1              ::Tesla::Key::F1
#define TL_KEY_F2              ::Tesla::Key::F2
#define TL_KEY_F3              ::Tesla::Key::F3
#define TL_KEY_F4              ::Tesla::Key::F4
#define TL_KEY_F5              ::Tesla::Key::F5
#define TL_KEY_F6              ::Tesla::Key::F6
#define TL_KEY_F7              ::Tesla::Key::F7
#define TL_KEY_F8              ::Tesla::Key::F8
#define TL_KEY_F9              ::Tesla::Key::F9
#define TL_KEY_F10             ::Tesla::Key::F10
#define TL_KEY_F11             ::Tesla::Key::F11
#define TL_KEY_F12             ::Tesla::Key::F12
#define TL_KEY_F13             ::Tesla::Key::F13
#define TL_KEY_F14             ::Tesla::Key::F14
#define TL_KEY_F15             ::Tesla::Key::F15
#define TL_KEY_F16             ::Tesla::Key::F16
#define TL_KEY_F17             ::Tesla::Key::F17
#define TL_KEY_F18             ::Tesla::Key::F18
#define TL_KEY_F19             ::Tesla::Key::F19
#define TL_KEY_F20             ::Tesla::Key::F20
#define TL_KEY_F21             ::Tesla::Key::F21
#define TL_KEY_F22             ::Tesla::Key::F22
#define TL_KEY_F23             ::Tesla::Key::F23
#define TL_KEY_F24             ::Tesla::Key::F24
#define TL_KEY_F25             ::Tesla::Key::F25

/* Keypad */
#define TL_KEY_KP_0            ::Tesla::Key::KP0
#define TL_KEY_KP_1            ::Tesla::Key::KP1
#define TL_KEY_KP_2            ::Tesla::Key::KP2
#define TL_KEY_KP_3            ::Tesla::Key::KP3
#define TL_KEY_KP_4            ::Tesla::Key::KP4
#define TL_KEY_KP_5            ::Tesla::Key::KP5
#define TL_KEY_KP_6            ::Tesla::Key::KP6
#define TL_KEY_KP_7            ::Tesla::Key::KP7
#define TL_KEY_KP_8            ::Tesla::Key::KP8
#define TL_KEY_KP_9            ::Tesla::Key::KP9
#define TL_KEY_KP_DECIMAL      ::Tesla::Key::KPDecimal
#define TL_KEY_KP_DIVIDE       ::Tesla::Key::KPDivide
#define TL_KEY_KP_MULTIPLY     ::Tesla::Key::KPMultiply
#define TL_KEY_KP_SUBTRACT     ::Tesla::Key::KPSubtract
#define TL_KEY_KP_ADD          ::Tesla::Key::KPAdd
#define TL_KEY_KP_ENTER        ::Tesla::Key::KPEnter
#define TL_KEY_KP_EQUAL        ::Tesla::Key::KPEqual

#define TL_KEY_LEFT_SHIFT      ::Tesla::Key::LeftShift
#define TL_KEY_LEFT_CONTROL    ::Tesla::Key::LeftControl
#define TL_KEY_LEFT_ALT        ::Tesla::Key::LeftAlt
#define TL_KEY_LEFT_SUPER      ::Tesla::Key::LeftSuper
#define TL_KEY_RIGHT_SHIFT     ::Tesla::Key::RightShift
#define TL_KEY_RIGHT_CONTROL   ::Tesla::Key::RightControl
#define TL_KEY_RIGHT_ALT       ::Tesla::Key::RightAlt
#define TL_KEY_RIGHT_SUPER     ::Tesla::Key::RightSuper
#define TL_KEY_MENU            ::Tesla::Key::Menu