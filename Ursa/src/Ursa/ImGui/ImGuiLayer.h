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
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void SetBlockEvents(bool blockEvents) { m_BlockEvents = blockEvents; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}