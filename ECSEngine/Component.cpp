#include "Component.h"

Component::Component(Entity* _entity, int _compId)
{
	m_entity = _entity;
	m_componentId = _compId;
}