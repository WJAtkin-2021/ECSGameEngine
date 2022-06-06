#pragma once
#include "Entity.h"

class ComponentLoaderEngine
{
public:
	virtual void LoadComponent(Entity* _entity, std::ifstream& _openFile, std::string _compName);

protected:
	ComponentLoaderEngine() { }
	~ComponentLoaderEngine() { }
};