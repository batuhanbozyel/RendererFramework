#pragma once

class SceneObject3D
{
public:
	friend class Renderer3D;
	virtual ~SceneObject3D() = default;

	virtual void Transform(const glm::mat4& transform) = 0;
protected:
	virtual const std::vector<uint32_t> CalculateIndices(uint32_t& offset) = 0;

	virtual inline const std::vector<Vertex>& GetData() const = 0;
	virtual inline uint32_t GetVertexSize() const = 0;
	virtual inline uint32_t GetIndexCount() const = 0;
protected:
	std::vector<Vertex> m_Data;
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

	virtual inline const std::vector<Vertex>& GetData() const override { return m_Data; }
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

	virtual inline const std::vector<Vertex>& GetData() const override { return m_Data;	}
	virtual inline uint32_t GetVertexSize() const { return (uint32_t)m_Data.size() * sizeof(Vertex); }
	virtual inline uint32_t GetIndexCount() const { return m_IndexCount; }
private:
	uint32_t m_IndexCount = 0;
	uint32_t m_SectorCount, m_StackCount;
};