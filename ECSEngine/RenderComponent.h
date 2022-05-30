#pragma once
#include "Component.h"

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
	void SetMesh(Mesh& _mesh) { m_mesh = &_mesh; }

	// Getters
	RenderComponent* GetThis() override { return this; }
	Mesh* GetMesh() { return m_mesh; }

private:
	Mesh* m_mesh = nullptr;
};