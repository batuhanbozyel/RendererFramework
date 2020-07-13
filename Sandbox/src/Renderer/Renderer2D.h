#pragma once
#include "Context.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Utility/Camera.h"

#include <glm/glm.hpp>

enum class MeshType;
class Mesh;

struct Vertex
{
	Vertex(const glm::vec3 pos)
		: Position(pos) {}

	Vertex(float x, float y, float z)
		: Position(x, y, z)	{}

	glm::vec3 Position;
};

class Renderer2D
{
public:
	static void Init();
	static void Shutdown();

	static void Draw(const OrthographicCamera& camera);

	static void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 3>>& datas);
	static void Submit(const std::string& name, const std::array<Vertex, 3>& data);

	static void Submit(const std::string& name, const std::initializer_list<std::array<Vertex, 4>>& datas);
	static void Submit(const std::string& name, const std::array<Vertex, 4>& data);
private:
	using ObjectMapValue = std::pair<std::shared_ptr<VertexBuffer>, uint32_t>;
	static std::unordered_map<std::string, ObjectMapValue> s_TriangleMap;
	static std::unordered_map<std::string, ObjectMapValue> s_QuadMap;

	static std::vector<std::shared_ptr<Mesh>> s_Meshes;

private:
	Renderer2D() = default;
};