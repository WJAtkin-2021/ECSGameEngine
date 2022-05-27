#pragma once
#include "Application.h"

class Window
{
public:

	virtual void Init() = 0;
	virtual void Loop();

	void SetApplication(Application* _app) { m_application = _app; }

protected:
	Window(int _screenWidth, int _screenHeight);
	~Window();

	int m_screenWidth;
	int m_screenHeight;

	Application* m_application;
};