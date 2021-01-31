#pragma once
#include"GL/glew.h"

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