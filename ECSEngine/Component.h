#pragma once

// For rendering the UI of each component
#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

class Entity;
class Component
{
public:
	virtual ~Component() = default;

	int GetCompId() { return m_componentId; }
	Entity& GetEntity() { return *m_entity; }

	virtual Component* GetThis() = 0;
	virtual void Update() = 0;
	virtual void StepPhysics() = 0;
	virtual bool DrawImGuiInterface() = 0;
	virtual void WriteDataToFile(std::ofstream& _saveFile) = 0;
	virtual void ReadDataFromFile(std::ifstream& _openFile) = 0;

protected:
	Component() = default;
	Component(Entity* _entity, int _compId);

	Entity* m_entity = nullptr;
	int m_componentId = -1;
};