#include "Texture.h"
#include "std_image/std_image.h"
Texture::Texture(const std::string& path) : m_RendererID(0), m_FilePath(path), 
	m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	/*Flip text vertically(make texture image upside down)
	since OpenGL acutally expect our texture start at the bottom left Not the Top left.
	So the bottom left in OpenGL is zero zero.
	Typically when we load images like PNG for example stores it in scan lines kind of
	From the top  of the image to the bottom of the image. So we need to actully flip it on load.	*/
	stbi_set_flip_vertically_on_load(1);	
	//load our texture image and get the information about texture.
	//Last parameter specify we use RGBa channel. 
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	//Generate Texture Buffer and bind it
	GLCall(glGenTextures(1,&m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	//Set 4 important parameter for our texture
	//1.Define how our texture being resample down when we need to rendering a image that smaller than texture image. 
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//2.Define how our texture being resample down when we need to rendering a image that bigger than texture image.
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//3 and 4 specify not extend the area of texture S and T represent X-Y axis
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	//Give OpenGL the texture data we load from png file.
	//Seconde parameter 0 indicate this is not a multiple texture.
	//Thrid parameter GL_RGBA indicate internal format. Internal format specify how OpenGL store the texture.
	//Sixth parameter specify the border size.
	//Seventh parameter indicate the format we of the texture we load.
	//Eighth parameter indicate the type of data.
	//Last parameter give the pointer to the texture data.
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//Unbind texture.
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	//GL_TEXTURE0 indicate we active texture slot0.
	//We have many slot you can use like GL_TEXTURE1,GL_TEXTURE2...
	//How many slot you have decided by your platform. Usually for PC is 32 for mobile phone is 8
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
