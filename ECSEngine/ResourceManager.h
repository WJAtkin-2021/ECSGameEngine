#pragma once
#include <memory>
#include <string>
#include <map>
#include "Mesh.h"
#include "Shader.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static Mesh& GetMesh(const std::string _filePath);
	static Mesh& GetMesh(const PrimitiveTypes _primativeType);

	static std::shared_ptr<Shader> GetShader(const ShaderType _shaderType);

private:
	static ResourceManager* m_instance;

	std::map<std::string, Mesh> m_meshMap;
	std::map<ShaderType, std::shared_ptr<Shader>> m_shaderMap;
};