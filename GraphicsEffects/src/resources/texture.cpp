#include "resources/texture.hpp"

#include "core/debug/assert.hpp"

#include "StbImage/stb_image.h"
#include <vector>
#include "core/maths/vector4.h"

#include "glad/glad.h"

Texture::~Texture()
{
	glDeleteTextures(1, &m_Handle);
}

void Texture::Load()
{
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_2D, m_Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	int32_t width;
	int32_t height;
	int32_t nbrChannels;
	const uint8_t* const data = stbi_load(m_Name.c_str(), &width, &height, &nbrChannels, 0);

	Assert::IsTrue(data != nullptr, std::string("Couldn't load texture : ").append(m_Name).c_str());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, nbrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete data;
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, m_Handle);
}
