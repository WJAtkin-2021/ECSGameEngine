#pragma once
#include "ApplicationUI.h"
#include "Entity.h"

class SandboxUI : public ApplicationUI
{
public:
	SandboxUI();
	~SandboxUI();

private:

	void DrawUI() override;
	void DrawTopBar();
	void DrawScenehierarchy();
	void DrawInspector();
	void DrawEnityInHierarchy(Entity* _entity);
	void DrawLightingWindow();
	void DrawRenderWindow();

	Entity* m_selectedEntity = nullptr;
};