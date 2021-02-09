#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/*
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
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//Error Handling
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(length));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to complie " << (type == GL_VERTEX_SHADER ? "vertexShader" : "fragmentShader") << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = ComplieShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = ComplieShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;

}
*/
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Specify the version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//Specify the version of OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	//Synchronize the screen refresh rate.
	glfwSwapInterval(1);

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

	{
		// Texture image in our case is flip upside down.
		// Texture coordinate start from left bottom is (0,0)
		float position[] = {    
		100.0f, 200.0f, 0.0f, 1.0f,    //Squre point 0
		200.0f, 200.0f, 1.0f, 1.0f,		//Squre point 1 Duplicated point
		100.0f, 100.0f, 0.0f, 0.0f,	//Squre point 2 Duplicated point
		200.0f, 100.0f, 1.0f, 0.0f		//Squre point 3
		}; //Define the data

		/*
		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao)); //Generate a veratex array object and get unique id.
		GLCall(glBindVertexArray(vao));		//Bind a vertex array object.
		*/
		VertexArray va;
		/*
		unsigned int buffer;
		GLCall(glGenBuffers(1, &buffer)); //Generate the buffer, buffer is used to store the unique id for that buffer
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); // Bind the buffer with current statement in another words select this buffer.
		GLCall(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), position, GL_STATIC_DRAW)); //Provide the buffer data and relative information
		*/
		VertexBuffer vb(position, 4 * 4 * sizeof(float));

		/*
		GLCall(glEnableVertexAttribArray(0)); //Specifies the index of the generic vertex attribute to be enabled or disabled.
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (const void*)0));
		*/
		VertexBufferLayout layout;
		layout.Push<float>(2); //Since our vertex is 2 dimensional the parameter is 2;
		layout.Push<float>(2); //Our vertex texture coordinate is 2 dimensional the parameter is 2;
		va.Addbuffer(vb, layout);

		unsigned int indices[] = {
			0,1,2, //The up triangle three vertex indices
			1,3,2  //The down triangle three vertex indices

		}; //Define the data
		
		//RGBa the "a" means alpha which decide how much transparent 
		//GL_ONE_MINUS_SRC_ALPHA just let it complete transparent.
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
		/*
		//Defince unique vertex indices buffer id
		unsigned int indexBuffer;
		//Generate the buffer, buffer is used to store the unique id for that buffer
		GLCall(glGenBuffers(1, &indexBuffer));
		// Since we bind a vertex array indices,here target is GL_ELEMENT_ARRAY_BUFFER.
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
		//Provide the buffer data and relative information
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));
		*/

		IndexBuffer ib(indices, 6);

		//1st parameter specify left boundary
		//2nd parameter specify right boundary
		//3rd parameter specify bottom boundary
		//4th parameter specify top boundary
		//5th parameter specify zNear boundary
		//6th parameter specify zfar boundary
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 mode = glm::translate(glm::mat4(1.0), glm::vec3(200, 200, 0));
		//view move right 100 pixels equal to object move left 100 pxiels
		glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(-100, 0, 0));
		glm::mat4 mvp = proj * view * mode;

		Shader shader("res/shader/basic.shader");
		shader.Bind();

		//ShaderProgramSource source = ParseShader("res/shader/basic.shader");
		//unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		//GLCall(glUseProgram(shader));

		//Get the id of uniform u_Color
		//First parameter indicate that uniform in which program.
		//Second parameter give the uniform name.

		shader.SetUniform4f("u_Color", 0.7, 0.2, 0.9, 1.0);
		shader.SetUniformMat4f("u_MVP", mvp);
		//GLCall(int u_Id = glGetUniformLocation(shader, "u_Color"));
		//ASSERT(u_Id != -1);
		//First parameter is the id(Location) of uniform
		//Remaind parameters are data you want to assign to that uniform.
		//GLCall(glUniform4f(u_Id, 0.7, 0.2, 0.9, 1.0));

		Texture texture("res/textures/penpen.png");
		//Textur Bind() function default value is 0.
		texture.Bind();
		
		//Since we bound our texture in slot 0
		shader.SetUniform1i("u_Texture", 0);
		

		float r = 0.0f;
		float increment = 0.05f;
		/* Loop until the user closes the window */

		/*
		GLCall(glUseProgram(0));//Cancle shader
		GLCall(glBindVertexArray(0));//Unbind vertex array object
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //Unbind vertex buffer
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); //Unbind index buffer
		*/
		va.Unbind();
		vb.UnBind();
		ib.UnBind();
		shader.UnBind();
		Renderer renderer;

		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			
			renderer.Clear();
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.2, 0.9, 1.0);

			renderer.Draw(va, ib, shader);

			//Based on r value change increment.
			increment = r > 1.0f ? -increment : increment;
			increment = r < 0.0f ? -increment : increment;
			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	
	}

	glfwTerminate();
	return 0;
}