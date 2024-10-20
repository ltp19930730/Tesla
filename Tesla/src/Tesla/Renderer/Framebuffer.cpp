#include "tlpch.h"
#include "Tesla/Renderer/Framebuffer.h"
#include "Tesla/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Tesla {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		TL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}