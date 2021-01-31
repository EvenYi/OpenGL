#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count):m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLint));
	//Generate the buffer, buffer is used to store the unique id for that buffer
	GLCall(glGenBuffers(1, &m_RendererID));
	// Since we bind a vertex array indices,here target is GL_ELEMENT_ARRAY_BUFFER.
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	//Provide the buffer data and relative information 
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}
