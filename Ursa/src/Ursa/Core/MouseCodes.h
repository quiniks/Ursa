#pragma once

namespace Ursa
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
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
		};
	}
}

/*
#define URSA_MOUSE_BUTTON_1         0
#define URSA_MOUSE_BUTTON_2         1
#define URSA_MOUSE_BUTTON_3         2
#define URSA_MOUSE_BUTTON_4         3
#define URSA_MOUSE_BUTTON_5         4
#define URSA_MOUSE_BUTTON_6         5
#define URSA_MOUSE_BUTTON_7         6
#define URSA_MOUSE_BUTTON_8         7
#define URSA_MOUSE_BUTTON_LAST      URSA_MOUSE_BUTTON_8
#define URSA_MOUSE_BUTTON_LEFT      URSA_MOUSE_BUTTON_1
#define URSA_MOUSE_BUTTON_RIGHT     URSA_MOUSE_BUTTON_2
#define URSA_MOUSE_BUTTON_MIDDLE    URSA_MOUSE_BUTTON_3
*/