#pragma once
#include <string>
#include <unordered_map>


struct ShaderProgramSource {
	std::string vertexShource;
	std::string fragmentSource;
};



class Shader
{

private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int>  m_UniformLocationCache;

	// caching for uniforms;

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind()const;
	void UnBind()const;


	//set uniform;
	
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);

};

