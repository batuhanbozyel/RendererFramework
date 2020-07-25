#pragma once
#include "Utility/Camera.h"
#include "Utility/SceneObject3D.h"

#include "Texture.h"

struct Meshes
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
	uint32_t Offset = 0;
};

enum class RendererMode
{
	_2D, _3D
};

class Renderer
{
public:
	static void Init(const RendererMode& mode);

	static void Draw(const OrthographicCamera& camera);
	static void Draw(const PerspectiveCamera& camera);

	static void Push(const std::shared_ptr<SceneObject3D>& object);

	static uint64_t CreateTexture(const char* path);
	static uint64_t DefaultTexture();

	static void TransformObject(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform);

	static void SetBackground(const glm::vec4& color);
	static void ClearColor();
protected:
	// To be defined in Renderer2D/Renderer3D
	virtual void PushObject(const std::shared_ptr<SceneObject3D>& object) = 0;

	virtual uint64_t AddTexture(const char* path) = 0;
	virtual uint64_t GetDefaultTexture() = 0;

	virtual void Transform(const std::shared_ptr<SceneObject3D>& object, const glm::mat4& transform) = 0;

	virtual inline const Meshes& GetMeshes() const = 0;
private:
	static std::unique_ptr<Renderer> s_Renderer;
	static glm::vec4 s_BackgroundColor;
};

