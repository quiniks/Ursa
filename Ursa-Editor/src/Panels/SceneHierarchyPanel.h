#pragma once
#include "Ursa/Core/Core.h"
#include "Ursa/Core/Log.h"
#include "Ursa/Scene/Scene.h"
#include "Ursa/Scene/Entity.h"

namespace Ursa {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);
		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}