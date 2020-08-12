#pragma once
#include "Utility/Camera.h"
#include "Utility/SceneObject3D.h"

struct WindowProps;

struct RenderData
{
	void Bind() const
	{
		VAO->Bind();
		Program->Bind();
	}

	std::unique_ptr<VertexArray> VAO;
	std::unique_ptr<Shader> Program;
	std::unique_ptr<Texture> Textures;

	// To decide pushing objects into which VertexBuffer
	std::shared_ptr<VertexBuffer> VertexBufferPtr;
	std::shared_ptr<IndexBuffer> IndexBufferPtr;
	uint32_t VertexOffset = 0;
	uint32_t IndexOffset = 0;

	uint32_t offset = 0;
};

enum class RendererMode
{
	_2D, _3D
};

class Renderer
{
public:
	static void Init(const RendererMode& mode, const WindowProps& props);

	static void Draw();

	static void Push(const std::shared_ptr<SceneObject3D>& object);
	static void TransformObject(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform);

	static const uint64_t CreateTexture(const char* path);
	static const uint64_t DefaultTexture();

	static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	static void SetBackground(const glm::vec4& color);
	static void ClearColor();

	inline static const std::unique_ptr<Camera>& GetCamera() { return s_Camera; }
protected:
	// To be defined in Renderer2D/Renderer3D
	virtual void PushObject(const std::shared_ptr<SceneObject3D>& object) = 0;
	virtual void Transform(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform) = 0;

	virtual const uint64_t AddTexture(const char* path) = 0;
	virtual const uint64_t GetDefaultTexture() = 0;

	virtual inline const RenderData& GetData() const = 0;
private:
	static std::unique_ptr<Renderer> s_Renderer;
	static glm::vec4 s_BackgroundColor;
	static std::unique_ptr<Camera> s_Camera;
};

