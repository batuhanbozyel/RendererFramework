#include "pch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::BindVertexBuffer(uint32_t slot)
{
	glVertexArrayVertexBuffer(m_RendererID, slot, m_VertexBuffers[slot]->m_RendererID, 0, m_VertexBuffers[slot]->m_Layout.GetStride());
}

void VertexArray::BindIndexBuffer(uint32_t slot)
{
	glVertexArrayElementBuffer(m_RendererID, m_IndexBuffers[slot]->m_RendererID);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	LOG_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer is empty!");

	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		glEnableVertexArrayAttrib(m_RendererID, m_VertexBufferIndex);

		switch (element.Type)
		{
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::UInt:
			case ShaderDataType::UInt2:
			case ShaderDataType::UInt3:
			case ShaderDataType::UInt4:
				glVertexArrayAttribIFormat(m_RendererID,
					m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Offset);
				break;
			default:
				glVertexArrayAttribFormat(m_RendererID,
					m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					element.Offset);
				break;
		}
		glVertexArrayAttribBinding(m_RendererID, m_VertexBufferIndex, m_VertexBufferCount);
		m_VertexBufferIndex++;
	}
	m_VertexBuffers.push_back(vertexBuffer);
	m_VertexBufferCount++;
}

void VertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	m_IndexBuffers.push_back(indexBuffer);
}