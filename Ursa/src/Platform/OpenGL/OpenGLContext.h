#pragma once

#include "Ursa/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Ursa {
	class OpenGLContext : public RenderContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
} 