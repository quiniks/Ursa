#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ursa {

	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
	{
		
	}

	void EditorLayer::OnAttach()
	{
		URSA_PROFILE_FUNCTION();
		m_CheckerTexture = Texture2D::Create("assets/textures/Checkerboard.png");
		m_TileSheet = Texture2D::Create("assets/textures/colored_transparent_packed.png");
		m_UrsaTitle = Texture2D::Create("assets/textures/Ursa.png");

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/Noto_Sans/NotoSans-Regular.ttf", 16.0f);
		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameRounding = 3.0f;
		//style.
		ImVec4* colors = style.Colors;
		//Colors
		{
			colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.58f, 0.58f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.07f, 0.08f, 0.09f, 0.50f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.04f, 0.04f, 0.04f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.18f, 0.20f, 0.54f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.18f, 0.20f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.53f, 0.56f, 0.67f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.18f, 0.20f, 1.00f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.08f, 0.09f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.69f, 0.68f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.54f, 0.69f, 0.68f, 0.40f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.44f, 0.53f, 0.56f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.07f, 0.08f, 0.09f, 0.70f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.18f, 0.20f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.07f, 0.08f, 0.09f, 0.70f);
			colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.18f, 0.20f, 0.66f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.15f, 0.18f, 0.20f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.07f, 0.08f, 0.09f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.53f, 0.56f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.15f, 0.18f, 0.20f, 0.95f);
			colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.28f, 0.32f, 0.86f);
			colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.84f, 0.73f, 0.80f);
			colors[ImGuiCol_TabActive] = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.18f, 0.20f, 0.97f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 0.84f, 0.73f, 0.70f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.58f, 0.28f, 0.35f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.54f, 0.69f, 0.68f, 1.00f);
		}


		m_CameraController.SetZoomLevel(5.0f);

		FrameBufferSpecification fbspec;
		fbspec.Width = 1280;
		fbspec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbspec);

		m_ActiveScene = CreateRef<Scene>();

		auto yellowQuad = m_ActiveScene->CreateEntity("Yellow");
		yellowQuad.AddComponent<SpriteComponent>(glm::vec4{ 0.9f, 0.9f, 0.6f, 1.0f });
		yellowQuad.GetComponent<TransformComponent>().Translation.x = -1.0f;

		auto redQuad = m_ActiveScene->CreateEntity("Blue");
		redQuad.AddComponent<SpriteComponent>(glm::vec4{ 0.4f, 0.8f, 0.8f, 1.0f });
		redQuad.GetComponent<TransformComponent>().Translation.x = 1.0f;

		m_QuadEntity = yellowQuad;

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
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		//Update
		if (m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		//Render
		Renderer2D::ResetStats();
		m_FrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
		m_ActiveScene->OnUpdate(ts);
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

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		static bool statsOpen = true;
		if (statsOpen) {
			ImGui::Begin("Stats", &statsOpen, ImGuiWindowFlags_NoCollapse);
			auto stats = Renderer2D::GetStats();
			ImGui::Text("Renderer2D stats");
			ImGui::Text("Draw calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			ImGui::End();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportSize.x, viewportSize.y };

		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();

		//ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}
}