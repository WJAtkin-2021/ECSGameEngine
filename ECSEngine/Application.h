#pragma once
#include "Renderer.h"

class Window;
class Application
{
public:
	Application(Window* _window, int _screenWidth, int _screenHeight);
	~Application();

	virtual void Init();
	virtual void Update();

protected:
	int m_screenWidth;
	int m_screenHeight;

	Window* m_window;
	Renderer* m_renderer;
};