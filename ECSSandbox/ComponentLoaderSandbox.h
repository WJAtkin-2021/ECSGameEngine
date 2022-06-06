#pragma once
#include "ComponentLoaderEngine.h"

class ComponentLoaderSandbox : public ComponentLoaderEngine
{
public:
	ComponentLoaderSandbox();
	~ComponentLoaderSandbox();

	void LoadComponent(Entity* _entity, std::ifstream& _openFile, std::string _compName) override;
};