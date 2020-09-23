#include "ursapch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ursa {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		URSA_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		URSA_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		URSA_CORE_ASSERT(status, "Failed to initialise Glad");

		URSA_CORE_INFO("OpenGL Info:");
		URSA_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		URSA_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		URSA_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		URSA_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}