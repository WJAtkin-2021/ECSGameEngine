#include <stdexcept>
#include <fstream>
#include "ComponentLoaderEngine.h"

void ComponentLoaderEngine::LoadComponent(Entity* _entity, std::ifstream& _openFile, std::string _compName)
{
	if (_compName == "Transform")
	{
		// The game object starts with a transform so just load the data onto it
		_entity->GetComponent<Transform>()->ReadDataFromFile(_openFile);
	}
	else if (_compName == "RenderComponent")
	{
		RenderComponent* rc = _entity->AddComponent<RenderComponent>();
		rc->ReadDataFromFile(_openFile);
	}
	else if (_compName == "MaterialComponent")
	{
		MaterialComponent* mc = _entity->AddComponent<MaterialComponent>();
		mc->ReadDataFromFile(_openFile);
	}
	else if (_compName == "LightComponent")
	{
		LightComponent* lc = _entity->AddComponent<LightComponent>();
		lc->ReadDataFromFile(_openFile);
	}
	else
	{
		// A load function for this has not been implemented so throw an error
		throw std::runtime_error("Tried to load component that does not have a load function implemented. Type: " + _compName);
	}
}