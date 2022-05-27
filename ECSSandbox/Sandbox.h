#pragma once
#include "Application.h"

class Sandbox : public Application
{
public:
	Sandbox(int _screenWidth, int _screenHight, HINSTANCE _hInstance);
	~Sandbox();

protected:
	int m_screenWidth;
	int m_screenHight;
};