#include "Shader.h"

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	CompileShader();
}

bool Shader::CompileShader() {

}

Shader::~Shader()
{
}

void Shader::Bind() const
{
}

void Shader::UnBind() const
{
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
}

unsigned int Shader::GEtUnifromLocation(const std::string& name)
{
	return 0;
}
