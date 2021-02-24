#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* data,unsigned int size);
	VertexBuffer(unsigned int size); //For dynamic vertex buffer
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;//OpenGL unique id
};