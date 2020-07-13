#pragma once
#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
	void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

	inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
	inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
private:
	uint32_t m_RendererID;
	uint32_t m_VertexBufferIndex;

	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};