#pragma once

#include "Ursa/Core/TimeStep.h"
#include "Ursa/Renderer/EditorCamera.h"
#include "Ursa/Renderer/FrameBuffer.h"
#include "entt.hpp"


namespace Ursa {
	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);
		void OnUpdateRuntime(TimeStep ts);
		void OnUpdateEditor(TimeStep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);
		int Pixel(int x, int y);
		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}