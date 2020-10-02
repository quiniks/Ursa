#pragma once
#include "Ursa/Core/KeyCodes.h"
#include "Ursa/Core/MouseCodes.h"

namespace Ursa {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode Key);

		static bool IsMouseButtonPressed(MouseCode button);
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<float, float> GetMousePos();
	};
}