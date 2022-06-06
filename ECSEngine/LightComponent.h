#pragma once
#include "Component.h"
#include "Light.h"

class LightComponent : public Component
{
public:

	LightComponent(Entity* _entity, int _compId);
	~LightComponent();

	// Getters
	LightComponent* GetThis() override { return this; }

	// Internal
	void Update() override;
	void StepPhysics() override {};
	bool DrawImGuiInterface() override;

private:

	Light* m_light;
};