#include "pch.h"
#include <glad/glad.h>
#include "Texture.h"
#include "Buffer.h"

#include "stb/stb_image.h"

constexpr uint32_t max_textures = 1024;

std::unique_ptr<Texture> TextureManager::s_Textures = nullptr;

Texture::Texture()
	: m_Count(0), m_IDs(max_textures)
{
	stbi_set_flip_vertically_on_load(1);
	m_SSBO.reset(new ShaderStorageBuffer(sizeof(TextureMaps) * max_textures, 0));

	glGenTextures(max_textures, m_IDs.data());
}

Texture::~Texture()
{
	for (const auto& id : m_IDs)
	{
		uint64_t handle = glGetTextureHandleARB(id);
		glMakeTextureHandleNonResidentARB(handle);
	}
	glDeleteTextures(max_textures, m_IDs.data());
}

void Texture::LoadTexture(const std::pair<std::string, TextureType>& texturePath)
{
	auto& textureIt = m_TextureMap.find(texturePath.first);
	if (textureIt == m_TextureMap.end())
	{
		if (m_Count < max_textures)
		{
			glBindTexture(GL_TEXTURE_2D, m_IDs[m_Count]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			int width, height, channels;
			unsigned char* buffer = stbi_load(texturePath.first.c_str(), &width, &height, &channels, 4);
			if (buffer)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
				uint64_t handle = glGetTextureHandleARB(m_IDs[m_Count]);
				glMakeTextureHandleResidentARB(handle);
				glBindTexture(GL_TEXTURE_2D, 0);
				m_SSBO->SetData(&handle, sizeof(TextureMaps) * m_Count + static_cast<size_t>(texturePath.second), sizeof(uint64_t));
				m_TextureMap.emplace(std::make_pair(texturePath.first, m_Count));
				stbi_image_free(buffer);
				return;
			}
			LOG_ERROR("Could not load texture!");
		}
		LOG_ERROR("Texture slots are occupied!");
		return;
	}
	uint64_t handle = glGetTextureHandleARB(m_IDs[textureIt->second]);
	m_SSBO->SetData(&handle, sizeof(TextureMaps) * m_Count + static_cast<size_t>(texturePath.second), sizeof(uint64_t));
}


// TextureManager

void TextureManager::Init()
{
	s_Textures.reset(new Texture());
}

uint32_t TextureManager::LoadTexture(const std::string& path)
{
	s_Textures->LoadTexture(std::make_pair(path, TextureType::Diffuse));
	s_Textures->LoadTexture(std::make_pair(path, TextureType::Specular));
	return s_Textures->m_Count++;
}

uint32_t TextureManager::LoadTextureMaps(const std::vector<std::pair<std::string, TextureType>>& texturePaths)
{
	for (const auto& path : texturePaths)
		s_Textures->LoadTexture(path);

	return s_Textures->m_Count++;
}
