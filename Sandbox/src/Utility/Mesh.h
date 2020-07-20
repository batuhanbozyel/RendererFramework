#pragma once
#include "Renderer/Context.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

struct Vertex
{
	Vertex(const glm::vec3& pos, const glm::vec4& color, const glm::vec2& tex)
		: Position(pos, 1.0f), Color(color), TexCoord(tex) {}

	Vertex(const glm::vec4& pos, const glm::vec4& color, const glm::vec2& tex)
		: Position(pos), Color(1.0f), TexCoord(tex) {}

	glm::vec4 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
};

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

	virtual void Bind() const override { s_Texture->Bind(0); s_VAO->Bind(); s_Program->Bind(); }
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
	std::unique_ptr<Texture> s_Texture;

	uint32_t s_Offset;
	std::shared_ptr<VertexBuffer> s_VertexBufferPtr;
};

class QuadMesh : public Mesh
{
public:
	QuadMesh();
	virtual ~QuadMesh() = default;
	virtual void Push(const Vertex* data) override;

	virtual void Bind() const override { s_Texture->Bind(0); s_VAO->Bind(); s_Program->Bind(); }
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
	std::unique_ptr<Texture> s_Texture;

	uint32_t s_Offset;
	std::shared_ptr<VertexBuffer> s_VertexBufferPtr;
};
