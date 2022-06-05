#pragma once
#include "Application.h"

class Sandbox : public Application
{
public:
	Sandbox(Window* _window, int _screenWidth, int _screenHeight);
	~Sandbox();

	void Init() override;
	void Update() override;

private:

	void ProcessKeyInput();

	float m_camSensitivity = 0.1f;
};