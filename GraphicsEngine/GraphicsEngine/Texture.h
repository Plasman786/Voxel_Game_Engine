#pragma once
#include "stb_image.h"
#include "Renderer.h"

class Texture 
{
private:
	unsigned int m_rendererID;
	std::string filepath;
	unsigned char* m_local_buffer;
	int m_width, m_height, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
	inline int getwidth() const { return m_width; };
	inline int getheight() const { return m_height; };
};