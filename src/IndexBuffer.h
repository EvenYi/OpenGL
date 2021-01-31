#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data,const unsigned int count);
	void Bind() const;
	void UnBind() const;
	unsigned int GetCount() const { return m_RendererID; }
	~IndexBuffer();

private:
	unsigned int m_RendererID;
	unsigned int m_Count;

};