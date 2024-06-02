#include "tlpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tesla {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}