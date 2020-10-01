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
		//Render 2D
		Camera* primaryCamera = nullptr;
		glm::mat4* primaryTransform = nullptr;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view) {
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary) {
				primaryCamera = &camera.Camera;
				primaryTransform = &transform.Transform;
				break;
			}
		}

		if (primaryCamera) {
			Renderer2D::BeginScene(primaryCamera->GetProjection(), *primaryTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
			for (auto entity : group) {
				auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//resize our non-fixed aspect ratio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& camera = view.get<CameraComponent>(entity);
			if (!camera.FixedAspectRatio) {
				camera
			}
		}
	}
}