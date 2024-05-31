#include "tlpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace  Tesla {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Tesla::ShaderDataType::Float:    return GL_FLOAT;
		case Tesla::ShaderDataType::Float2:   return GL_FLOAT;
		case Tesla::ShaderDataType::Float3:   return GL_FLOAT;
		case Tesla::ShaderDataType::Float4:   return GL_FLOAT;
		case Tesla::ShaderDataType::Mat3:     return GL_FLOAT;
		case Tesla::ShaderDataType::Mat4:     return GL_FLOAT;
		case Tesla::ShaderDataType::Int:      return GL_INT;
		case Tesla::ShaderDataType::Int2:     return GL_INT;
		case Tesla::ShaderDataType::Int3:     return GL_INT;
		case Tesla::ShaderDataType::Int4:     return GL_INT;
		case Tesla::ShaderDataType::Bool:     return GL_BOOL;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		TL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexArrayAttrib(m_RendererID, index);
			glVertexArrayAttribFormat(m_RendererID, index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				element.Offset);
			// Associate attributes with binding points
			glVertexArrayAttribBinding(m_RendererID, index, index);
			// Bind the buffer to the VAO's vertex buffer binding point
			glVertexArrayVertexBuffer(m_RendererID, index, vertexBuffer->GetId(), 0, layout.GetStride());
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glVertexArrayElementBuffer(m_RendererID, indexBuffer->GetId());

		m_IndexBuffer = indexBuffer;
	}

}