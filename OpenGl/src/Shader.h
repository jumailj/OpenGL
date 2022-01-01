#pragma once
#include <string>

class Shader
{

private:
	std::string m_FilePath;
	unsigned int m_RendererID;

	// caching for uniforms;

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind()const;
	void UnBind()const;


	//set uniform;
	
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	bool CompileShader();
	unsigned int GEtUnifromLocation(const std::string& name);

};

