#include "Texture.h"

Texture::Texture(const std::string& path): m_rendererID(0), filepath(path), m_local_buffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	 
	glGenTextures(1, &m_rendererID);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (!m_local_buffer) {
		std::cerr << "Failed to load texture at path: " << path << std::endl;
	}
	if (m_local_buffer) {
		stbi_image_free(m_local_buffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}
void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}