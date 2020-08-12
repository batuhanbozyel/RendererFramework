#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	const uint64_t LoadTexture(const char* path);

	const uint64_t DefaultTexture() const { return m_Handles[0]; }
	const uint64_t DefaultTextureFromMap() const { return m_Handles[m_TextureMap.find(std::string())->second]; }
private:
	std::vector<uint32_t> m_IDs;
	std::vector<uint64_t> m_Handles;

	std::unordered_map<std::string, int> m_TextureMap;

	int m_Count = 0;
};