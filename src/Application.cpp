#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);
	std::string line;
	//Create stringstream to store source code
	std::stringstream ss[2];
	//Create emun to specify type of shader
	enum class shadertype {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT =1
	};
	shadertype type = shadertype::NONE;
	while (std::getline(stream, line)) {

		//find a start index of a shader code
		if (line.find("#shader") != std::string::npos) {
			//Check which type shader
			if (line.find("vertex") != std::string::npos) {
				//set type to vertex
				type = shadertype::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//set type to fragment
				type = shadertype::FRAGMENT;
			}
		}
		else {
			//using the type as index
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int ComplieShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(length));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to complie " << (type == GL_VERTEX_SHADER ? "vertexShader" : "fragmentShader") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = ComplieShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = ComplieShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;

	}
	std::cout << glewGetString(GL_VERSION_1_1) << std::endl;

	float position[6] = { -0.5,-0.5,0,0.5,0.5,-0.5 }; //Define the data

	unsigned int buffer;
	glGenBuffers(1, &buffer); //Generate the buffer, buffer is used to store the unique id for that buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // Bind the buffer with current statement in another words select this buffer.
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW); //Provide the buffer data and relative information 

	glEnableVertexAttribArray(0); //Specifies the index of the generic vertex attribute to be enabled or disabled.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (const void*)0);

	ShaderProgramSource source = ParseShader("res/shader/basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3); //Tell openGL to use selected buffer to draw a triangle.
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}