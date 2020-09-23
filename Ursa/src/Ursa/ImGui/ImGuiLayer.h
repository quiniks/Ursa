#pragma once

#include "Ursa/Core/Layer.h"
#include "Ursa/Events/ApplicationEvent.h"
#include "Ursa/Events/KeyEvent.h"
#include "Ursa/Events/MouseEvent.h"

namespace Ursa {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}