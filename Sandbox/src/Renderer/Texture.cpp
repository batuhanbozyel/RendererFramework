#include "pch.h"
#include "Texture.h"

#include "stb/stb_image.h"

constexpr uint32_t max_textures = 1024;

Texture::Texture()
	: m_Count(0)
{
	m_IDs.resize(max_textures, 0);
	m_Handles.resize(max_textures, 0);

	glGenTextures(max_textures, m_IDs.data());

	glBindTexture(GL_TEXTURE_2D, m_IDs[m_Count]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char buffer[4] = { 255, 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	m_Handles[m_Count] = glGetTextureHandleARB(m_IDs[m_Count]);
	glMakeTextureHandleResidentARB(m_Handles[m_Count]);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_TextureMap.insert(std::make_pair(std::string(), m_Count++));
}

Texture::~Texture()
{
	for (const auto& texture : m_Handles)
	{
		glMakeTextureHandleNonResidentARB(texture);
	}
	glDeleteTextures(max_textures, m_IDs.data());
}

const uint64_t Texture::LoadTexture(const char* path)
{
	auto& textureIt = m_TextureMap.find(path);
	if (textureIt == m_TextureMap.end())
	{
		glBindTexture(GL_TEXTURE_2D, m_IDs[m_Count]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		unsigned char* buffer = stbi_load(path, &width, &height, &channels, 4);
		if (buffer)
		{
			if (m_Count < max_textures)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
				m_Handles[m_Count] = glGetTextureHandleARB(m_IDs[m_Count]);
				glMakeTextureHandleResidentARB(m_Handles[m_Count]);
				glBindTexture(GL_TEXTURE_2D, 0);
				uint64_t handle = m_Handles[m_Count];
				m_TextureMap.insert(std::make_pair(path, m_Count++));
				stbi_image_free(buffer);
				return handle;
			}
			LOG_WARN("Texture slots are occupied!");
			stbi_image_free(buffer);
		}
		LOG_ERROR("Could not load texture!");
		return DefaultTextureFromMap();
	}
	
	return m_Handles[textureIt->second];
}