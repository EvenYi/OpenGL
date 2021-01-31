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