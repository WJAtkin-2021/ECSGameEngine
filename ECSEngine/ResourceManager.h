#pragma once
#include <memory>
#include <string>
#include <map>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static Mesh& GetMesh(const std::string _filePath);
	static Mesh& GetMesh(const PrimitiveTypes _primativeType);

	static std::shared_ptr<Shader> GetShader(const ShaderType _shaderType);

	static Texture& GetTexture(const std::string _filePath);

private:
	static ResourceManager* m_instance;

	std::map<std::string, Mesh> m_meshMap;
	std::map<std::string, std::shared_ptr<Texture>> m_textureMap;
	std::map<ShaderType, std::shared_ptr<Shader>> m_shaderMap;
};