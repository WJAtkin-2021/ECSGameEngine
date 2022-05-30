#pragma once
#include <string>
#include <map>
#include "Mesh.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static Mesh& GetMesh(const std::string _filePath);
	static Mesh& GetMesh(const PrimitiveTypes _primativeType);

private:
	static ResourceManager* m_instance;

	std::map<std::string, Mesh> m_meshMap;
};