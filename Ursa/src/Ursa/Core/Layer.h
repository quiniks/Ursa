#pragma once

#include "Ursa/Core/Core.h"
#include "Ursa/Events/Event.h"
#include "Ursa/Core/TimeStep.h"

namespace Ursa {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep timeStep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}