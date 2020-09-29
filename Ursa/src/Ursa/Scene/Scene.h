#pragma once
#include "entt.hpp"
#include "Ursa/Core/TimeStep.h"

namespace Ursa {
	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());
		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}