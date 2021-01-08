#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ursa/Scene/SceneSerializer.h"
#include "Ursa/Utils/PlatformUtils.h"
#include "imguizmo/ImGuizmo.h"
#include "Ursa/Math/Math.h"
#include "fontawesome/FontAwesome5.h"

namespace Ursa {

	EditorLayer::EditorLayer()
		:Layer("EditorLayer")//, m_CameraController(1280.0f / 720.0f, true)
	{
		
	}

	void EditorLayer::OnAttach()
	{
		URSA_PROFILE_FUNCTION();
		m_CheckerTexture = Texture2D::Create("assets/textures/Checkerboard.png");
		m_TileSheet = Texture2D::Create("assets/textures/colored_transparent_packed.png");
		m_UrsaTitle = Texture2D::Create("assets/textures/Ursa.png");

		//Fonts
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-Bold.ttf", 16.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-Regular.ttf", 16.0f);
		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 16.0f;
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		io.Fonts->AddFontFromFileTTF("assets/fonts/FontAwesome5/fa-solid-900.ttf", 16.0f, &config, icon_ranges);
		
		//Style
		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameRounding = 3.0f;
		//Colors
		{
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.58f, 0.58f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.04f, 0.04f, 0.04f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.18f, 0.20f, 0.50f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.44f, 0.53f, 0.56f, 0.53f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.69f, 0.68f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.149f, 0.180f, 0.200f, 0.000f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.149f, 0.180f, 0.200f, 1.000f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.18f, 0.20f, 0.50f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.28f, 0.32f, 0.50f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.28f, 0.32f, 0.50f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.69f, 0.68f, 0.51f);
			colors[ImGuiCol_TabActive] = ImVec4(0.54f, 0.69f, 0.68f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 0.84f, 0.73f, 0.70f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.58f, 0.28f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.54f, 0.69f, 0.68f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		}

		//m_CameraController.SetZoomLevel(5.0f);

		FrameBufferSpecification fbspec;
		fbspec.Width = 1280;
		fbspec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbspec);
		//m_IDFrameBuffer = FrameBuffer::Create(fbspec);

		m_ActiveScene = CreateRef<Scene>();

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

#if 0
		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>();
		

		class CameraController : public ScriptableEntity {
		public:
			void OnUpdate(TimeStep ts) {
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * ts;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * ts;
			}
		};
		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
		URSA_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(TimeStep ts)
	{
		URSA_PROFILE_FUNCTION();

		//Resize
		if (FrameBufferSpecification fbspec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && 
			(fbspec.Width != m_ViewportSize.x || fbspec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//m_IDFrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		//Update
		if (m_ViewportFocused) {
			m_EditorCamera.OnUpdate(ts);
		}
		

		//Render
		Renderer2D::ResetStats();
		m_FrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		m_FrameBuffer->Bind();
		//Update Scene
		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		auto viewportHeight = m_ViewportBounds[1].y - m_ViewportBounds[0].y;
		auto viewportWidth = m_ViewportBounds[1].x - m_ViewportBounds[0].x;
		my = viewportHeight - my;
		int mxi = (int)mx;
		int myi = (int)my;
		if (mxi >= 0.0f && myi >= 0.0f && mxi < viewportWidth && myi < viewportHeight) {
			int pixel = m_ActiveScene->Pixel(mx, my);
			m_HoveredEntity = pixel == -1 ? Entity() : Entity((entt::entity)pixel, m_ActiveScene.get());
			URSA_CORE_WARN("ID: {0}", pixel);
		}

		m_FrameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		URSA_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();
				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();
				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Translate"))
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				if (ImGui::MenuItem("Rotate"))
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				if (ImGui::MenuItem("Scale"))
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
				if (ImGui::MenuItem("None"))
					m_GizmoType = -1;
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("ImGui Demo"))
					m_DemoOpen = true;
				if (ImGui::MenuItem("Render Statistics"))
					m_StatsOpen = true;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 2.0f, 0 });
		if (ImGui::Button(ICON_FA_MOUSE_POINTER))
			m_GizmoType = -1;
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_ARROWS_ALT))
			m_GizmoType = 0;
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_SYNC_ALT))
			m_GizmoType = 1;
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_EXPAND_ARROWS_ALT))
			m_GizmoType = 2;
		ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSize = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize.x = minWinSize;

		m_SceneHierarchyPanel.OnImGuiRender();
		
		if (m_StatsOpen) {
			ImGui::Begin("Stats", &m_StatsOpen, ImGuiWindowFlags_NoCollapse);

			auto stats = Renderer2D::GetStats();
			ImGui::Text("Renderer2D stats");
			ImGui::Text("Draw calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			
			std::string name = "Null";
			if ((entt::entity)m_HoveredEntity != entt::null)
				name = m_HoveredEntity.GetComponent<TagComponent>().Tag;
			ImGui::Text("Hovered Entity: %s", name.c_str());
			
			ImGui::End();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
		ImGui::Begin("Viewport");

		auto viewportOffset = ImGui::GetCursorPos();

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportSize.x, viewportSize.y };

		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		
		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;
		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

		//Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (m_GizmoType != -1 && selectedEntity) {
			float rw = (float)ImGui::GetWindowWidth();
			float rh = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, rw, rh);

			//Selected Entity
			TransformComponent& selectedEntityTransformComponent = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 selectedEntityTransform = selectedEntityTransformComponent.GetTransform();

			bool snapKey = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f;
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;
			float snapValues[3] = { snapValue, snapValue, snapValue };

			//ImGuizmo::DrawGrid(glm::value_ptr(cameraView), glm::value_ptr(camera.GetProjection()), glm::value_ptr(glm::mat4(1.0f)), 10.f);
			
			ImGuizmo::Manipulate(
				glm::value_ptr(m_EditorCamera.GetView()),
				glm::value_ptr(m_EditorCamera.GetProjection()),
				(ImGuizmo::OPERATION)m_GizmoType,
				ImGuizmo::LOCAL,
				glm::value_ptr(selectedEntityTransform),
				nullptr,
				snapKey ? snapValues : nullptr
			);

			if (ImGuizmo::IsUsing()) {
				glm::vec3 trans, scale, rot;
				Math::DecomposeTransform(selectedEntityTransform, trans, rot, scale);
				glm::vec3 deltaR = rot - selectedEntityTransformComponent.Rotation;

				selectedEntityTransformComponent.Translation = trans;
				selectedEntityTransformComponent.Rotation += deltaR;
				selectedEntityTransformComponent.Scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
		
		if (m_DemoOpen)
			ImGui::ShowDemoWindow(&m_DemoOpen);
	}

	void EditorLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(URSA_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(URSA_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool CTRL = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool SHIFT = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode())
		{
		case Key::N:
		{
			if (CTRL)
				NewScene();

			break;
		}
		case Key::O:
		{
			if (CTRL)
				OpenScene();

			break;
		}
		case Key::S:
		{
			if (CTRL && SHIFT)
				SaveSceneAs();

			break;
		}
		case Key::Q:
			if (CTRL)
				m_GizmoType = -1;
			break;
		case Key::W:
			if (CTRL)
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case Key::E:
			if (CTRL)
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		case Key::R:
			if (CTRL)
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonEvent& e)
	{
		return false;
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::string filePath = FileDialogs::OpenFile("Ursa Scene (*.ursa)\0*.ursa\0");
		if (!filePath.empty()) {
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filePath);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filePath = FileDialogs::SaveFile("Ursa Scene (*.ursa)\0*.ursa\0");
		if (!filePath.empty()) {
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filePath);
		}
	}
}