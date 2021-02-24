#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); //Generate the buffer, buffer is used to store the unique id for that buffer
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind the buffer with current statement in another words select this buffer.
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); //Provide the buffer data and relative information 
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	GLCall(glCreateBuffers(1, &m_RendererID)); //Generate the buffer, buffer is used to store the unique id for that buffer
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind the buffer with current statement in another words select this buffer.
	GLCall(glBufferData(GL_ARRAY_BUFFER, size*100, nullptr, GL_DYNAMIC_DRAW)); //Provide the buffer data and relative information
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind the buffer with current statement in another words select this buffer.
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind the buffer.
}
