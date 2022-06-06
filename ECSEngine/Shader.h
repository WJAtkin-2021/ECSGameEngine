#pragma once
#include <string>
#include <memory>

enum class ShaderType : unsigned int
{
	INVALID = 0,
	// ********* HLSL *********
	Vertex_HLSL = 1,
	VertexSkyBox_HLSL = 2,
	PixelFallBack_HLSL = 3,
	PixelTextured_HLSL = 4,
	PixelSkyBox_HLSL = 5,
	PixelBumpMapped_HLSL = 6,

	// ********* GLSL *********
	Vertex_GLSL = 7,
	VertexSkyBox_GLSL = 8,
	FragmentFallBack_GLSL = 9,
	FragmentTextured_GLSL = 10,
	FragmentSkyBox_GLSL = 11,
};

class Shader
{
public:
	Shader();
	~Shader();

	static std::shared_ptr<Shader> FactoryCreateShader();

	virtual void LoadShader(ShaderType _shaderType) = 0;
	virtual void SetVertexShaderForDrawCall() = 0;
	virtual void SetPixelShaderForDrawCall() = 0;
};