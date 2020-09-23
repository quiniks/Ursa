#include "ursapch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ursa{
	RendererAPI * RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}