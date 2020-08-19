#include "pch.h"
#include "Buffer.h"

/////////// VertexBuffer ///////////

VertexBuffer::VertexBuffer(uint32_t size, BufferUsage usage)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, static_cast<GLenum>(usage));
}

VertexBuffer::VertexBuffer(const float* vertices, uint32_t size, BufferUsage usage)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, static_cast<GLenum>(usage));
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const float* vertices, uint32_t offset, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
}

/////////// IndexBuffer ///////////

IndexBuffer::IndexBuffer(uint32_t count, BufferUsage usage)
	: m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), nullptr, static_cast<GLenum>(usage));
}

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage)
	: m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, static_cast<GLenum>(usage));
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const uint32_t* indices, uint32_t offset, uint32_t count)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeof(uint32_t) * count, indices);
}

/////////// ShaderStorageBuffer ///////////

ShaderStorageBuffer::ShaderStorageBuffer(uint32_t size, uint32_t location, BufferUsage usage)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, static_cast<GLenum>(usage));
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, location, m_RendererID);
}

ShaderStorageBuffer::~ShaderStorageBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void ShaderStorageBuffer::Bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
}

void ShaderStorageBuffer::Unbind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBuffer::SetData(const void* data, uint32_t offset, uint32_t size)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
}
