#pragma once

#pragma pack(push, 1)
struct Vertex
{
	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec4& color, const glm::vec2& tex, uint64_t handle = 0)
		: Position(pos, 1.0f), Normal(normal), Color(color), TexCoord(tex), TexHandle(handle) {}

	Vertex(const glm::vec4& pos, const glm::vec3& normal, const glm::vec4& color, const glm::vec2& tex, uint64_t handle = 0)
		: Position(pos), Normal(normal), Color(1.0f), TexCoord(tex), TexHandle(handle) {}

	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	uint64_t TexHandle;
};
#pragma pack(pop)

class SceneObject3D
{
public:
	friend class Renderer3D;
	virtual ~SceneObject3D() = default;

	virtual void Transform(const glm::mat4& transform) = 0;
protected:
	virtual const std::vector<uint32_t> CalculateIndices(uint32_t& offset) = 0;

	inline const std::vector<Vertex>& GetData() const { return m_Vertices; }

	virtual inline uint32_t GetVertexSize() const = 0;
	virtual inline uint32_t GetIndexCount() const = 0;
protected:
	std::vector<Vertex> m_Vertices;
};

class Cuboid : public SceneObject3D
{
public:
	// Length, Color, Texture Handle
	explicit Cuboid(glm::vec3 length, const glm::vec4& color = glm::vec4(1.0f), uint64_t handle = 0);
	~Cuboid() = default;

	virtual void Transform(const glm::mat4& transform) override;
private:
	virtual const std::vector<uint32_t> CalculateIndices(uint32_t& offset) override;

	virtual inline uint32_t GetVertexSize() const { return 24 * sizeof(Vertex); }
	virtual inline uint32_t GetIndexCount() const override { return 36; }
};

class Sphere : public SceneObject3D
{
public:
	// Radius, Sector and Stack count, Color, Texture Handle
	explicit Sphere(float radius, uint32_t sectorCount = 18, uint32_t stackCount = 18, const glm::vec4& color = glm::vec4(1.0f), uint64_t handle = 0);
	~Sphere() = default;

	virtual void Transform(const glm::mat4& transform) override;
private:
	virtual const std::vector<uint32_t> CalculateIndices(uint32_t& offset) override;

	virtual inline uint32_t GetVertexSize() const { return (uint32_t)m_Vertices.size() * sizeof(Vertex); }
	virtual inline uint32_t GetIndexCount() const { return m_IndexCount; }
private:
	uint32_t m_IndexCount = 0;
	uint32_t m_SectorCount, m_StackCount;
};