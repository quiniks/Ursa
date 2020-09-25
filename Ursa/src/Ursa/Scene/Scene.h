#pragma once
#include "entt.hpp"
#include "Ursa/Core/TimeStep.h"

namespace Ursa {
	class Scene {
	public:
		Scene();
		~Scene();
		entt::entity CreateEntity();
		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;
	};
}