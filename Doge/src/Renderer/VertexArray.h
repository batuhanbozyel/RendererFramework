#pragma once
#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void BindVertexBuffer(uint32_t slot);
	void BindIndexBuffer(uint32_t slot);

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
	inline const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const { return m_IndexBuffers; }
private:
	uint32_t m_RendererID;
	uint32_t m_VertexBufferIndex = 0;
	uint32_t m_VertexBufferCount = 0;

	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::vector<std::shared_ptr<IndexBuffer>> m_IndexBuffers;
};