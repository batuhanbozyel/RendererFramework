#pragma once

class SceneObject3D
{
public:
	friend class Renderer3D;
	virtual ~SceneObject3D() = default;

	virtual void Transform(const glm::mat4& transform) = 0;
protected:
	virtual inline const std::vector<Vertex>& GetData() const = 0;
	virtual inline uint32_t GetSize() const = 0;
};

class Cuboid : public SceneObject3D
{
public:
	explicit Cuboid(glm::vec3 length, const glm::vec4& color, uint64_t handle = 0);
	~Cuboid() = default;

	virtual void Transform(const glm::mat4& transform) override;
private:
	virtual inline const std::vector<Vertex>& GetData() const override { return m_Data; };
	virtual inline uint32_t GetSize() const { return 24 * sizeof(Vertex); }
private:
	std::vector<Vertex> m_Data;
};