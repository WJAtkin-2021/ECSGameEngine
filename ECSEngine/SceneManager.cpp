#include <fstream>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Camera.h"

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

Light* SceneManager::CreateNewLight()
{
	Light* newLight = new Light();
	m_instance->m_lights.push_back(newLight);
	return newLight;
}

void SceneManager::RemoveLight(Light* _light)
{
	for (size_t i = 0; i < m_instance->m_lights.size(); i++)
	{
		if (m_instance->m_lights[i] == _light)
		{
			m_instance->m_lights.erase(m_instance->m_lights.begin() + i);
			delete _light;
			return;
		}
	}
}

const std::vector<Light*> SceneManager::GetEnabledLights()
{
	std::vector<Light*> activeLights;

	for (size_t i = 0; i < m_instance->m_lights.size(); i++)
	{
		if (m_instance->m_lights[i]->Enabled())
		{
			activeLights.push_back(m_instance->m_lights[i]);
		}
	}

	return activeLights;
}

bool SceneManager::HasValidSavePath()
{
	if (m_instance->m_workingFilePath == "")
	{
		return false;
	}
	return true;
}

void SceneManager::NewScene()
{
	m_instance->RemoveAllEntities();
	m_instance->m_workingFilePath = "";

	// TODO: Set window captions
	//Engine::GetWindow()->SetWindowCaption("*New Scene");
}

void SceneManager::RemoveAllEntities()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	}
	m_entities.resize(0);
	m_currentFreeId = 0;
	// TODO: Reset inspector
	//Engine::GetUI()->Reset();
}

void SceneManager::SaveSceneToFile(const std::string& _filePath)
{
	// Open up the ofstream
	std::ofstream saveFile(_filePath);
	if (!saveFile)
	{
		throw std::runtime_error("Cannot open scene file: " + _filePath);
		return;
	}

	// Save meta data
	saveFile << "<?xml version=""1.0""?>\n";
	saveFile << "<!--Scene File Version 2.0-->\n\n";
	saveFile << "<Scene>\n";

	// Save camera data as camera is not an entity
	Camera::GetCamera()->WriteDataToFile(saveFile);

	// Save the ambient lighting data
	saveFile << "<AmbientLighting> ";
	saveFile << m_ambientColor.m_x << " " << m_ambientColor.m_y << " " << m_ambientColor.m_z;
	saveFile << " </AmbientLighting>\n";

	// Loop through all entities
	for (int i = 0; i < m_entities.size(); i++)
	{
		Entity* currentEntity = m_entities[i];
		saveFile << "<Entity>\n";
		{
			saveFile << "<EntityName> " << currentEntity->GetName() << " </EntityName>\n";
			const Vector3D color = currentEntity->GetColor();
			saveFile << "<EntityColor> " << color.m_x << " " << color.m_y << " " << color.m_z << " </EntityColor>\n";
			saveFile << "<Components>\n";
			std::vector<Component*> components = currentEntity->GetComponents();
			for (int j = 0; j < components.size(); j++)
			{
				components[j]->WriteDataToFile(saveFile);
			}
			saveFile << "</Components>\n";
		}
		saveFile << "</Entity>\n";
	}

	saveFile << "</Scene>\n";

	// Close the file
	saveFile.close();
	m_workingFilePath = _filePath;

	// TODO: Set the window caption
	//Engine::GetWindow()->SetWindowCaption(_filePath);
}

void SceneManager::OpenSceneFromFile(const std::string& _filePath)
{
	// Open up the ifstream
	std::ifstream openFile(_filePath);
	if (!openFile)
	{
		throw std::runtime_error("Can not open scene file: " + _filePath);
	}

	// Remove everything in the current scene
	NewScene();

	// Read and verify meta data
	std::string data = "";
	while (openFile >> data && data != "<Scene>") {}

	// Read the camera data from file
	Camera::GetCamera()->ReadDataFromFile(openFile);

	// Read the ambient 
	while (openFile >> data && data != "<AmbientLighting>") {}
	openFile >> data;
	m_ambientColor.m_x = std::stof(data);
	openFile >> data;
	m_ambientColor.m_y = std::stof(data);
	openFile >> data;
	m_ambientColor.m_z = std::stof(data);

	// Loop through each game object until we hit the </Scene> tag
	while (openFile >> data && data != "</Scene>")
	{
		Entity* newEntity = CreateEntity();
		while (openFile >> data && data != "</Entity>")
		{
			if (data == "<ClassName>")
			{
				// Make sure this was a game object that we are loading
				openFile >> data; openFile >> data;
				if (data != "Entity")
				{
					throw std::runtime_error("GameObject expected in scene file got something else instead");
				}
			}
			else if (data == "<EntityName>")
			{
				openFile >> data;
				newEntity->SetName(data);
			}
			else if (data == "<EntityColor>")
			{
				Vector3D entityColor;
				openFile >> data;
				entityColor.m_x = std::stof(data);
				openFile >> data;
				entityColor.m_y = std::stof(data);
				openFile >> data;
				entityColor.m_z = std::stof(data);
				newEntity->SetColor(entityColor);
			}

			// Loop through all the components until we hit the </Components> tag
			else if (data == "<Components>")
			{
				while (data != "</Components>")
				{
					if (data == "<ClassName>")
					{
						// Grab the name of the component
						openFile >> data;

						// Pass the open file to the component loader class for loading the component
						// The engine will have a base version of this class that will load in the engine
						// components and then the tanks game project will implement a class that derives
						// from this to load in the components that are specific to the game.
						m_compLoader->LoadComponent(newEntity, openFile, data);
					}

					// Get next part of data
					openFile >> data;
				}
			}
		}
	}

	// TODO: Set the window caption
	//Engine::GetWindow()->SetWindowCaption(_filePath);
}