#pragma once
#include "Renderer/Renderer2D.h"

enum class MeshType {
	TRIANGLE,
	QUAD
};

class Mesh
{
public:
	virtual ~Mesh() = default;
	static std::shared_ptr<Mesh> Create(const MeshType& type);

	virtual void Push(const Vertex* data) = 0;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual inline uint32_t GetOffset() const = 0;
	virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
	virtual inline const std::shared_ptr<VertexBuffer>& GetVertexBufferPtr() const = 0;
	virtual inline const std::shared_ptr<Shader>& GetShader() const = 0;
};

class TriangleMesh : public Mesh
{
public:
	TriangleMesh();
	virtual ~TriangleMesh() = default;
	virtual void Push(const Vertex* data) override;

	virtual void Bind() const override { s_VAO->Bind(); s_Program->Bind(); }
	virtual void Unbind() const override { s_VAO->Unbind(); s_Program->Unbind(); }

	virtual inline uint32_t GetOffset() const override { return s_Offset; }
	virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return s_VAO->GetIndexBuffer(); }
	virtual inline const std::shared_ptr<VertexBuffer>& GetVertexBufferPtr() const override { return s_VertexBufferPtr; }
	virtual inline const std::shared_ptr<Shader>& GetShader() const override { return s_Program; }
private:
	static uint32_t* CalculateIndices();
private:
	std::unique_ptr<VertexArray> s_VAO;
	std::shared_ptr<Shader> s_Program;

	uint32_t s_Offset;
	std::shared_ptr<VertexBuffer> s_VertexBufferPtr;
};

class QuadMesh : public Mesh
{
public:
	QuadMesh();
	virtual ~QuadMesh() = default;
	virtual void Push(const Vertex* data) override;

	virtual void Bind() const override { s_VAO->Bind(); s_Program->Bind(); }
	virtual void Unbind() const override { s_VAO->Unbind(); s_Program->Unbind(); }

	virtual inline uint32_t GetOffset() const override { return s_Offset; }
	virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return s_VAO->GetIndexBuffer(); }
	virtual inline const std::shared_ptr<VertexBuffer>& GetVertexBufferPtr() const override { return s_VertexBufferPtr; }
	virtual inline const std::shared_ptr<Shader>& GetShader() const override { return s_Program; }
private:
	static uint32_t* CalculateIndices();
private:
	std::unique_ptr<VertexArray> s_VAO;
	std::shared_ptr<Shader> s_Program;

	uint32_t s_Offset;
	std::shared_ptr<VertexBuffer> s_VertexBufferPtr;
};
