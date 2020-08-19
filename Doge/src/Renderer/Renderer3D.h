#pragma once
#include "Renderer.h"

class Renderer3D : public Renderer
{
public:
	Renderer3D();
	~Renderer3D() = default;

private:
	virtual void PushObject(const std::shared_ptr<SceneObject3D>& object) override;
	virtual void Transform(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform) override;

	virtual inline const RenderData& GetData() const override { return m_Data; }
private:
	RenderData m_Data;

	// Cache for transforming or removing objects faster
	struct ObjectMapValue
	{
		ObjectMapValue(const std::shared_ptr<SceneObject3D>& objectPtr, 
					   const std::shared_ptr<VertexBuffer>& vbPtr, 
					   const std::shared_ptr<IndexBuffer>& ibPtr, 
					   const uint32_t vOffset, const uint32_t iOffset)
			: Object(objectPtr), VertexBufferPtr(vbPtr), IndexBufferPtr(ibPtr), VertexOffset(vOffset), IndexOffset(iOffset)
		{

		}

		const std::shared_ptr<SceneObject3D>& Object;
		const std::shared_ptr<VertexBuffer>& VertexBufferPtr;
		const std::shared_ptr<IndexBuffer>& IndexBufferPtr;
		const uint32_t VertexOffset;
		const uint32_t IndexOffset;
	};
	std::unordered_map<std::shared_ptr<SceneObject3D>, ObjectMapValue> m_ObjectCache;
};