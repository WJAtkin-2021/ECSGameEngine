#pragma once
#include "Application.h"

class Sandbox : public Application
{
public:
	Sandbox(int _screenWidth, int _screenHeight);
	~Sandbox();

	void Init() override;
	void Loop() override;
};