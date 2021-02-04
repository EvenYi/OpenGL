#pragma once
#include <string>
#include <unordered_map>


struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();
	void Bind() const;
	void UnBind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int ComplieShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
	
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;//Used to cache store each uniform location.


};