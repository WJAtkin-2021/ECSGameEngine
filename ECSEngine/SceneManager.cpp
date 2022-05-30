#include "SceneManager.h"
#include "Entity.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	m_instance = this;
}

SceneManager::~SceneManager()
{
	// Remove all entities
	for (size_t i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	}
}

// Returns an empty entity
Entity* SceneManager::CreateEntity()
{
	Entity* newEntity = new Entity(m_instance->m_currentFreeId);
	m_instance->m_currentFreeId++;
	m_instance->m_entities.push_back(newEntity);
	return newEntity;
}

// Finds an entity via pointer and deletes + removes from list
void SceneManager::RemoveEntity(Entity* _removee)
{
	for (size_t i = 0; i < m_instance->m_entities.size(); i++)
	{
		if (m_instance->m_entities[i] == _removee)
		{
			delete m_instance->m_entities[i];
			m_instance->m_entities.erase(m_instance->m_entities.begin() + i);
		}
	}
}