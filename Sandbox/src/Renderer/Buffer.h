#pragma once
#include "ShaderDataType.h"

struct Vertex
{
	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec4& color, const glm::vec2& tex, uint64_t handle = 0.0f)
		: Position(pos, 1.0f), Color(color), TexCoord(tex), TexHandle(handle) 
	{

	}

	Vertex(const glm::vec4& pos, const glm::vec4& color, const glm::vec2& tex, uint64_t handle = 0.0f)
		: Position(pos), Color(1.0f), TexCoord(tex), TexHandle(handle) {}

	glm::vec4 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	uint64_t TexHandle;
};

enum class BufferUsage
{
	STATIC = GL_STATIC_DRAW,
	DYNAMIC = GL_DYNAMIC_DRAW,
	STREAM = GL_STREAM_DRAW
};

struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	uint32_t Size;
	uint64_t Offset;
	bool Normalized;
	bool AttribIPointer;

	BufferElement(ShaderDataType type, const std::string& name, bool attribI = false, bool normalized = false)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), AttribIPointer(attribI) ,Normalized(normalized)
	{
	}

	uint32_t GetComponentCount() const
	{
		switch (Type)
		{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::UInt:    return 1;
			case ShaderDataType::UInt2:   return 2;
			case ShaderDataType::UInt3:   return 3;
			case ShaderDataType::UInt4:   return 4;
			case ShaderDataType::Bool:    return 1;
		}

		LOG_ASSERT(false, "Unknown ShaderDataType specified!");
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout()
		: m_Stride(0) {}

	BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements), m_Stride(0)
	{
		uint32_t offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	inline uint32_t GetStride() const { return m_Stride; }
	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride;
};

class VertexBuffer
{
public:
	VertexBuffer(uint32_t size, BufferUsage usage = BufferUsage::DYNAMIC);
	VertexBuffer(const float* vertices, uint32_t size, BufferUsage usage = BufferUsage::DYNAMIC);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const float* vertices, uint32_t offset, uint32_t size);
	const BufferLayout& GetLayout() const { return m_Layout; }
	void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
private:
	uint32_t m_RendererID;
	BufferLayout m_Layout;
};

class IndexBuffer
{
public:
	IndexBuffer(uint32_t count, BufferUsage usage = BufferUsage::DYNAMIC);
	IndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage = BufferUsage::DYNAMIC);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const uint32_t* indices, uint32_t offset, uint32_t count);
	inline uint32_t GetCount() const { return m_Count; }
private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};