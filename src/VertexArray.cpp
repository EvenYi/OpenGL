#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID)); //Generate a veratex array object and get unique id.
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Addbuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {

		const auto& item = elements[i];
		GLCall(glEnableVertexAttribArray(i)); //Specifies the index of the generic vertex attribute to be enabled or disabled.
		GLCall(glVertexAttribPointer(i, item.count, item.type, item.normalized, layout.GetStride(), (const void*)offset));
		offset += item.count * VertexBufferElement::GetSizeOfType(item.type);
	}
	
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));		//Bind a vertex array object.
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
