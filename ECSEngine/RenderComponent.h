#pragma once
#include "Component.h"
#include "PrimativeTypes.h"

class Mesh;
class RenderComponent : public Component
{
public:
	RenderComponent() = default;
	RenderComponent(Entity* _entity, int _compId);
	~RenderComponent();

	void Update() override {};
	void StepPhysics() override {};
	bool DrawImGuiInterface() override;

	// Setters
	void SetMesh(Mesh& _mesh);
	void RemoveMesh();

	// Getters
	RenderComponent* GetThis() override { return this; }
	Mesh* GetMesh() { return m_mesh; }

private:
	Mesh* m_mesh = nullptr;

	PrimitiveTypes m_meshPrimative = PrimitiveTypes::INVALID;
	std::string m_meshFilePath = "";
};