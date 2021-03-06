#pragma once
#include "Ursa.h"

#include "imgui/imgui.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Ursa/Renderer/EditorCamera.h"

namespace Ursa {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
		
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		EditorCamera m_EditorCamera;
		Ref<Scene> m_ActiveScene;
		Entity m_QuadEntity;
		Entity m_CameraEntity;
		Entity m_HoveredEntity;

		Ref<VertexArray> m_SquareVertexArray;
		Ref<Shader> m_FlatColorShader;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Texture2D> m_CheckerTexture;

		Ref<Texture2D> m_TileSheet;
		Ref<Texture2D> m_UrsaTitle;
		std::unordered_map<char, Ref<SubTexture2D>> m_TextureMap;
		uint32_t m_MapWidth = 0, m_MapHeight = 0;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportBounds[2];

		//Panels
		bool m_StatsOpen = false;
		bool m_DemoOpen = false;
		SceneHierarchyPanel m_SceneHierarchyPanel;

		//Gizmos
		int m_GizmoType = 0;
	};
}