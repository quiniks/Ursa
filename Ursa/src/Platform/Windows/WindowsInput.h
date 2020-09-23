#pragma once

#include "Ursa/Core/Input.h"

namespace Ursa {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseYImpl() override;
		virtual float GetMouseXImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}