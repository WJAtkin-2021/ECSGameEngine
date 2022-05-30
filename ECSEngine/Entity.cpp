#include "Entity.h"

Entity::Entity(int _id)
{
	m_id = _id;
}

Entity::~Entity()
{
	// Remove all components
	for (size_t i = 0; i < m_components.size(); i++)
	{
		delete m_components[i];
	}
}