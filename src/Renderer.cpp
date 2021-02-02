#include"Renderer.h"
#include<iostream>
void GLClearError() {
	// While all error flags have not been clear this loop will not stop
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	//While error == GL_NO_ERROR(0) auto break loop.
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error Code] (" << error << ")" << std::endl;
		std::cout << "[OpenGL File Path ] (" << file << ")" << std::endl;
		std::cout << "[OpenGL Last Call ] (" << function << ")" << std::endl;
		std::cout << "[OpenGL Code Line ] (" << line << ")" << std::endl;

		return false;
	}
	return true;
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	//First parameter Specifies what kind of primitives to render.
	//Second parameter indicate we using 6 vertex array indices.
	//Third parameter indicate the type of array indices element.
	//Forth parameter the pointer to vertex array indices buffer, 
	//since we already bind it, this parameter is nullptr
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
