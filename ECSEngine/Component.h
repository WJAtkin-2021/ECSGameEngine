#pragma once

class Entity;
class Component
{
public:
	virtual Component* GetThis() = 0;
	virtual ~Component() = default;

	int GetCompId() { return m_componentId; }
	Entity& GetEntity() { return *m_entity; }

protected:
	Component() = default;
	Component(Entity* _entity, int _compId);

	Entity* m_entity = nullptr;
	int m_componentId = -1;
};