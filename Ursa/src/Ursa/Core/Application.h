#pragma once

#include "Core.h"
#include "Window.h"

#include "Ursa/Core/LayerStack.h"
#include "Ursa/Events/Event.h"
#include "Ursa/Events/ApplicationEvent.h"
#include "Ursa/ImGui/ImGuiLayer.h"
#include "Ursa/Core/TimeStep.h"


namespace Ursa {

	class Application {
	public:
		Application(const std::string& name = "Ursa");
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

		void Close();
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;
	private:
		static Application* s_Instance;
	};

	//Define in client
	Application* CreateApplication();
}