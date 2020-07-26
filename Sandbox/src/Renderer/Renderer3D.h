#pragma once
#include "Renderer.h"

class Renderer3D : public Renderer
{
public:
	Renderer3D();
	~Renderer3D() = default;

private:
	virtual void PushObject(const std::shared_ptr<SceneObject3D>& object) override;

	virtual uint64_t AddTexture(const char* path) override;
	virtual uint64_t GetDefaultTexture() override;

	virtual void Transform(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform) override;

	virtual inline const Meshes& GetMeshes() const override { return m_Meshes; }
private:
	Meshes m_Meshes;

	// Cache for transforming or removing objects faster
	struct ObjectMapValue
	{
		std::shared_ptr<SceneObject3D> Object;
		std::shared_ptr<VertexBuffer> VertexBufferPtr;
		std::shared_ptr<IndexBuffer> IndexBufferPtr;
		uint32_t VertexOffset;
		uint32_t IndexOffset;
	};
	std::unordered_map<std::shared_ptr<SceneObject3D>, ObjectMapValue> m_ObjectCache;
};