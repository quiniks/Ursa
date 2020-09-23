#include "Ursapch.h"
#include "Ursa/Core/Window.h"

#ifdef URSA_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Ursa
{
	Scope<Window> Window::Create(const WindowProperties& props)
	{
#ifdef URSA_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		URSA_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}