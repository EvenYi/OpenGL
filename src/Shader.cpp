#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string& filePath) : m_FilePath(filePath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	//Create stringstream to store source code
	std::stringstream ss[2];
	//Create emun to specify type of shader
	enum class shadertype {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
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

unsigned int Shader::ComplieShader(unsigned int type, const std::string& source)
{
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

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
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

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "[Warning]: Uniform " << name << " does not exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
