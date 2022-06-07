#pragma once
#include <vector>
#include "Entity.h"
#include "PrimativeTypes.h"
#include "Light.h"
#include "ComponentLoaderEngine.h"

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
	static const std::vector<Light*> GetEnabledLights();

	// For scene management
	static void SaveScene() { m_instance->SaveSceneToFile(m_instance->m_workingFilePath); }
	static void SaveSceneAs(const std::string& _filePath) { m_instance->SaveSceneToFile(_filePath); }
	static void OpenScene(const std::string& _filePath) { m_instance->OpenSceneFromFile(_filePath); }
	static void NewScene();
	static bool HasValidSavePath();

	// Returns a list of all entities
	static std::vector<Entity*> GetEntites() { return m_instance->m_entities; }

	// Sets the component loader, should be called from the game project using the derived
	// component loader class
	static void SetComponentLoader(std::shared_ptr<ComponentLoaderEngine> _compLoader) { m_instance->m_compLoader = _compLoader; }


private:
	// Helpers
	void RemoveAllEntities();
	void SaveSceneToFile(const std::string& _filePath);
	void OpenSceneFromFile(const std::string& _filePath);

	// Instance handle of the scene manager
	static SceneManager* m_instance;

	// For managing entities
	std::vector<Entity*> m_entities;
	int m_currentFreeId = 0;

	// For managing lights in the scene
	std::vector<Light*> m_lights;
	Vector3D m_ambientColor = Vector3D(0.5f, 0.5f, 0.5f);

	// Current filepath of the scene
	std::string m_workingFilePath = "";

	// Component loader
	std::shared_ptr<ComponentLoaderEngine> m_compLoader;
};