#pragma once
#include <vector>
#include <stdexcept>
#include <string>

// Components
#include "Component.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "MaterialComponent.h"
#include "LightComponent.h"

class Entity
{
public:
	Entity() = default;
	Entity(int _id);
	~Entity();

	// Getters
	std::string GetName() { return m_name; }
	int GetId() { return m_id; }
	Vector3D GetColor() { return m_color; }
	std::vector<Component*> GetComponents() { return m_components; }

	// Setters
	void SetName(std::string _name) { m_name = _name; }
	void SetColor(Vector3D _newColor) { m_color = _newColor; }

	bool DrawImGuiInterface();

	// Return the first instance of this component
	template<typename T>
	T* GetComponent() const
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (typeid(*(m_components[i]->GetThis())) == typeid(T))
			{
				T* comp = (static_cast<T*>(m_components[i]));
				return comp;
			}
		}
	
		// If not found then throw an error
		throw std::invalid_argument("GameObject does not have component of this type");
	}
	
	// Check if the entity has this component
	template<typename T>
	bool HasComponent() const
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (typeid(*(m_components[i]->GetThis())) == typeid(T))
				return true;
		}
		return false;
	}
	
	// Adds a component by the type name of the template
	template<typename T>
	T* AddComponent()
	{
		T* newComponent = new T(this, m_nextCompId);
		m_nextCompId++;
		m_components.push_back(dynamic_cast<Component*>(newComponent));
		return newComponent;
	}

private:

	void DeleteComponent(int _compId);

	// Id and name for the entity
	int m_id = -1;
	std::string m_name = "New Entity";

	// Component list
	std::vector<Component*> m_components;
	int m_nextCompId = 0;

	// Color of the entity, used for fall back rendering
	Vector3D m_color = Vector3D(1.0f, 0.0f, 1.0f);
};