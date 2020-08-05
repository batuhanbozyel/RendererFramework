#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	const uint64_t DefaultTexture() const { return m_Handles[0]; }
	const uint64_t LoadTexture(const char* path);
private:
	std::vector<uint32_t> m_IDs;
	std::vector<uint64_t> m_Handles;

	int m_Count = 0;
};