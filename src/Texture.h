#pragma once
#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	//In OpenGL we have various slots(32 or 8), each slots contain a texture.
	//Your can choose which slot you want to bing.
	//Here we give the slot parameter a default value slot 0. 
	void Bind(unsigned int slot=0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};