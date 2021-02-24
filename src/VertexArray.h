#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Addbuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Addbuffer(const VertexBuffer& vb); //For dynamic buffer
	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;

};