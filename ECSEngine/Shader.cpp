#include "Shader.h"
#include "Shader_DX11.h"

Shader::Shader() { }

Shader::~Shader() { }

std::shared_ptr<Shader> Shader::FactoryCreateShader()
{
#ifdef BUILD_DX_11
	return std::shared_ptr<Shader>(new Shader_DX11());
#elif BUILD_OpenGL
	return std::shared_ptr<Shader>(new Shader_GL());
#endif
}