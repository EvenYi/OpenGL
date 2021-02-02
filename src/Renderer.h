#pragma once
#include "GL/glew.h"
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

#define ASSERT(x) if(!(x)) __debugbreak();
// Fisrt we call GLClearError funtion.
// Then we call the OpenGL function x
// Finally we call ASSERT(GLLogCall()) to check error.
// #x transfer call function to string
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	Renderer();
	~Renderer();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;

private:


};