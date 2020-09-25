#include "ursapch.h"
#include "Scene.h"
#include "Components.h"
#include <glm/glm.hpp>

namespace Ursa {
	Scene::Scene()
	{
		struct TransformComponent {
			glm::mat4 Transform;
			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform) : Transform(transform) {}
			operator const glm::mat4& () { return Transform; }
		};

		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity);
	}

	Scene::~Scene()
	{

	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(TimeStep ts)
	{

	}
}