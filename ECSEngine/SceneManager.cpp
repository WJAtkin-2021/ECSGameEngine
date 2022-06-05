#include "SceneManager.h"
#include "ResourceManager.h"
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
	// Create and add to the list
	Entity* newEntity = new Entity(m_instance->m_currentFreeId);
	m_instance->m_currentFreeId++;
	m_instance->m_entities.push_back(newEntity);

	// Add the transform as this is a requirement for all entities in this engine
	newEntity->AddComponent<Transform>();

	return newEntity;
}

Entity* SceneManager::CreatePrimative(PrimitiveTypes _primativeType)
{
	Entity* newEntity = CreateEntity();
	RenderComponent* rc = newEntity->AddComponent<RenderComponent>();

	switch (_primativeType)
	{
	case PrimitiveTypes::INVALID:
		throw std::runtime_error("INVALID Primitive Type");
		break;
	case PrimitiveTypes::Cube:
		rc->SetMesh(ResourceManager::GetMesh(PrimitiveTypes::Cube));
		break;
	case PrimitiveTypes::Sphere:
		throw std::runtime_error("INVALID Primitive Type");
		break;
	default:
		throw std::runtime_error("INVALID Primitive Type");
		break;
	}

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
			return;
		}
	}
}