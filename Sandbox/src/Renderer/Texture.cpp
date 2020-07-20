#include "pch.h"
#include "Texture.h"
#include <glad/glad.h>

#include "stb/stb_image.h"

Texture2D::Texture2D(const char* filePath)
{
	stbi_set_flip_vertically_on_load(1);
	int width, height, bpp;
	unsigned char* buffer = stbi_load(filePath, &width, &height, &bpp, 4);

	LOG_ASSERT(buffer, "Cannot Open Texture file!");

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (buffer)
		stbi_image_free(buffer);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_ID);
}

void Texture2D::Bind(uint32_t slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
