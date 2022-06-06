#pragma once
#include <vector>
#include "Entity.h"
#include "PrimativeTypes.h"
#include "Light.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// For entity management
	static Entity* CreateEntity();
	static Entity* CreatePrimative(PrimitiveTypes _primativeType);
	static void RemoveEntity(Entity* _removee);

	// For light management
	static Light* CreateNewLight();
	static void RemoveLight(Light* _light);
	static Vector3D& GetAmbientRBG() { return m_instance->m_ambientColor; }
	static void SetAmbientRGB(const Vector3D& _newColor) { m_instance->m_ambientColor = _newColor; }
	const std::vector<Light*> GetEnabledLights() const;

	// Returns a list of all entities
	static std::vector<Entity*> GetEntites() { return m_instance->m_entities; }

private:

	// Instance handle of the scene manager
	static SceneManager* m_instance;

	// For managing entities
	std::vector<Entity*> m_entities;
	int m_currentFreeId = 0;

	// For managing lights in the scene
	std::vector<Light*> m_lights;
	Vector3D m_ambientColor = Vector3D(0.5f, 0.5f, 0.5f);
};