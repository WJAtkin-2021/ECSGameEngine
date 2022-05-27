#pragma once
#include "ApplicationUI.h"

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

};