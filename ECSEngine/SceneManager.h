#pragma once
#include <vector>
#include "Entity.h"
#include "PrimativeTypes.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// For entity management
	static Entity* CreateEntity();
	static Entity* CreatePrimative(PrimitiveTypes _primativeType);
	static void RemoveEntity(Entity* _removee);

	// Returns a list of all entities
	static std::vector<Entity*> GetEntites() { return m_instance->m_entities; }

private:

	// Instance handle of the scene manager
	static SceneManager* m_instance;

	// For managing entities
	std::vector<Entity*> m_entities;
	int m_currentFreeId = 0;
};