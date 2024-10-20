#include "tlpch.h"
#include "Tesla/Renderer/VertexArray.h"

#include "Tesla/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Tesla {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		TL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}