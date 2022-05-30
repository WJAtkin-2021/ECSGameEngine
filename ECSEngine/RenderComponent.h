#pragma once
#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent() = default;
	RenderComponent(Entity* _entity, int _compId);
	~RenderComponent();

	RenderComponent* GetThis() override { return this; }
	void Update() override = 0;
	void StepPhysics() override = 0;
	bool DrawImGuiInterface() override = 0;
};