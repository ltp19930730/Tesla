#include "tlpch.h"
#include "Tesla/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tesla {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();;

}