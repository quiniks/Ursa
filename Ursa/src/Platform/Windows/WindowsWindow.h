#pragma once

#include "Ursa/Core/Window.h"
#include "Ursa/Renderer/RenderContext.h"
#include <GLFW/glfw3.h>


namespace Ursa {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		RenderContext* m_Context;

		struct WindowData {
			std::string Title = "";
			unsigned int Width = 1080, Height = 720;
			bool VSync = true;
			EventCallbackFn EventCallback = nullptr;
		} m_Data;
	};
}