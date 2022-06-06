#include "ComponentLoaderSandbox.h"

ComponentLoaderSandbox::ComponentLoaderSandbox() : ComponentLoaderEngine() { }

ComponentLoaderSandbox::~ComponentLoaderSandbox() { }

void ComponentLoaderSandbox::LoadComponent(Entity* _entity, std::ifstream& _openFile, std::string _compName)
{
	// Since no component loader function was found call the base class
	ComponentLoaderEngine::LoadComponent(_entity, _openFile, _compName);

}