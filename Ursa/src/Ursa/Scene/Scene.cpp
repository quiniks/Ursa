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

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		//Update scripts

		m_Registry.view<NativeScriptComponent>().each([=](entt::entity entity, NativeScriptComponent& nsc) {
			//todo move to scene::onsceneplay
			if (!nsc.Instance) {
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_Entity = Entity{ entity, this };
				nsc.Instance->OnCreate();
			}
			nsc.Instance->OnUpdate(ts);
		});
		////
		//Render 2D
		Camera* primaryCamera = nullptr;
		glm::mat4 primaryTransform;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view) {
			auto [transformComponent, cameraComponent] = view.get<TransformComponent, CameraComponent>(entity);
			if (cameraComponent.Primary) {
				primaryCamera = &cameraComponent.Camera;
				primaryTransform = transformComponent.GetTransform();
				break;
			}
		}

		if (primaryCamera) {
			Renderer2D::BeginScene(primaryCamera->GetProjection(), primaryTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
			for (auto entity : group) {
				auto [transformComponent, spriteComponent] = group.get<TransformComponent, SpriteComponent>(entity);
				Renderer2D::DrawQuad(transformComponent.GetTransform(), spriteComponent.Color);
			}

			Renderer2D::EndScene();
		}
		////
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//resize our non-fixed aspect ratio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}

	bool Scene::GetPrimaryCameraEntity(Entity& camera)
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view) {
			auto cameraComponent = view.get<CameraComponent>(entity);
			if (cameraComponent.Primary) {
				camera = Entity{ entity, this };
				return true;
			}
		}
		return false;
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component) {
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) {}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) {
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component) {}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component) {}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component) {}
}