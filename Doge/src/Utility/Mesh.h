#pragma once

#pragma pack(push, 1)
struct Vertex
{
	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, const glm::vec4& color = glm::vec4(1.0f), uint64_t handle = 0)
		: Position(pos, 1.0f), Normal(normal), Color(color), TexCoord(tex), TexHandle(handle) {}

	Vertex(const glm::vec4& pos, const glm::vec3& normal, const glm::vec2& tex, const glm::vec4& color = glm::vec4(1.0f), uint64_t handle = 0)
		: Position(pos), Normal(normal), Color(color), TexCoord(tex), TexHandle(handle) {}

	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec4 Color;
	glm::vec2 TexCoord;
	uint64_t TexHandle;
};
#pragma pack(pop)

enum class TextureType {
	Specular,
	Diffuse
};

struct TextureHandle
{
	uint64_t Handle;
	TextureType Type;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::vector<TextureHandle> textures)
		: m_Vertices(vertices), m_Indices(indices), m_Textures(textures) {}

private:
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
	std::vector<TextureHandle> m_Textures;
};