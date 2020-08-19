#pragma once

class ShaderStorageBuffer;
class TextureManager;

struct TextureMaps
{
	uint64_t DiffuseMap;
	uint64_t SpecularMap;
};

enum class TextureType {
	Diffuse = offsetof(TextureMaps, DiffuseMap),
	Specular = offsetof(TextureMaps, SpecularMap)
};

class Texture
{
public:
	friend class TextureManager;
	~Texture();
private:
	Texture();

	void LoadTexture(const std::pair<std::string, TextureType>& texturePath);
private:
	std::vector<uint32_t> m_IDs;

	std::unique_ptr<ShaderStorageBuffer> m_SSBO;
	std::unordered_map<std::string, uint32_t> m_TextureMap;

	uint32_t m_Count = 0;
};

class TextureManager
{
public:
	static void Init();

	static uint32_t LoadTexture(const std::string& path);
	static uint32_t LoadTextureMaps(const std::vector<std::pair<std::string, TextureType>>& texturePaths);
private:
	static std::unique_ptr<Texture> s_Textures;
};