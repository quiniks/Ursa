#include "ursapch.h"
#include "Scene.h"
#include "Components.h"
#include "Ursa/Renderer/Renderer2D.h"
#include "Entity.h"
#include <glm/glm.hpp>

namespace Ursa {
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
		for (auto entity : group) {
			auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}