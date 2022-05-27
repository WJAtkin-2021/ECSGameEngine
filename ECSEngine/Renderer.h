#pragma once
#include "UI.h"

class Renderer
{
public:
	virtual void InitGraphicsAPI(int _screenWidth, int _screenHeight) = 0;
	virtual void DrawScene() = 0;

	virtual ~Renderer();

protected:
	Renderer();

	int m_screenWidth = 0;
	int m_screenHeight = 0;

	// UI class that sets up and manages ImGui
	UI* m_UI = nullptr;
};