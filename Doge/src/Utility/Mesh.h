#pragma once
#include "Material.h"

#pragma pack(push, 1)
struct Vertex
{
	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, uint32_t index = 0)
		: Position(pos, 1.0f), Normal(normal), TexCoord(tex), TexIndex(index) {}

	Vertex(const glm::vec4& pos, const glm::vec3& normal, const glm::vec2& tex, uint32_t index = 0)
		: Position(pos), Normal(normal), TexCoord(tex), TexIndex(index) {}

	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	uint32_t TexIndex;
};
#pragma pack(pop)

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
		: m_Vertices(vertices), m_Indices(indices) {}

private:
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
};