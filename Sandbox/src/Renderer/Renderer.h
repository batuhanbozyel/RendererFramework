#pragma once
#include "Utility/Mesh.h"
#include "Utility/Camera.h"

#include <glm/glm.hpp>

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

	static void PushTriangle(const std::string& name, const std::array<Vertex, 3>& data);
	static void PushTriangleMesh(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas);

	static void PushQuad(const std::string& name, const std::array<Vertex, 4>& data);
	static void PushQuadMesh(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas);

	static void ClearColor(const glm::vec4& color);
	static void Clear();
protected:
	// Triangle Mesh submits
	virtual void Submit(const std::string& name, const std::array<Vertex, 3>& data) = 0;
	virtual void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas) = 0;

	// Quad Mesh submits
	virtual void Submit(const std::string& name, const std::array<Vertex, 4>& data) = 0;
	virtual void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas) = 0;
private:
	static std::unique_ptr<Renderer> s_Renderer;
};

