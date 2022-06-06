#include <stdexcept>
#include "ResourceManager.h"

ResourceManager* ResourceManager::m_instance = nullptr;

ResourceManager::ResourceManager()
{
	m_instance = this;
}

ResourceManager::~ResourceManager() { }

Mesh& ResourceManager::GetMesh(const std::string _filePath)
{
	// Firstly search for the mesh in the map
	auto search = m_instance->m_meshMap.find(_filePath);
	if (search == m_instance->m_meshMap.end())
	{
		// If not found then load in a new mesh
		m_instance->m_meshMap[_filePath] = Mesh(_filePath);
	}

	return m_instance->m_meshMap[_filePath];
}

Mesh& ResourceManager::GetMesh(const PrimitiveTypes _primativeType)
{
	// Convert the PrimativeType into a key for the map
	std::string key;
	switch (_primativeType)
	{
	case PrimitiveTypes::Cube:
		key = "Cube";
		break;
	case PrimitiveTypes::Sphere:
		key = "Sphere";
		break;
	default:
		throw std::invalid_argument("Primitive type unhandled");
	}

	// Then search for the mesh in the map
	auto search = m_instance->m_meshMap.find(key);
	if (search == m_instance->m_meshMap.end())
	{
		// If not found then load in a new mesh
		m_instance->m_meshMap[key] = Mesh(_primativeType);
	}

	return m_instance->m_meshMap[key];
}

std::shared_ptr<Shader> ResourceManager::GetShader(const ShaderType _shaderKey)
{
	// Firstly search for the shader in the map
	auto search = m_instance->m_shaderMap.find(_shaderKey);
	if (search == m_instance->m_shaderMap.end())
	{
		// If not found then load in a new shader
		m_instance->m_shaderMap[_shaderKey] = Shader::FactoryCreateShader();
		m_instance->m_shaderMap[_shaderKey]->LoadShader(_shaderKey);
	}

	return m_instance->m_shaderMap[_shaderKey];
}

Texture& ResourceManager::GetTexture(const std::string _filePath)
{
	// Firstly search for the texture in the map
	auto search = m_instance->m_textureMap.find(_filePath);
	if (search == m_instance->m_textureMap.end())
	{
		// If not found then load the texture in
		m_instance->m_textureMap[_filePath] = Texture::FactoryCreateTexture();
		m_instance->m_textureMap[_filePath]->LoadTexture(_filePath);
	}

	return *(m_instance->m_textureMap[_filePath]);
}