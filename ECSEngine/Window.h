#pragma once
#include "Application.h"

class Window
{
public:

	virtual void Init() = 0;
	virtual void Loop();
	virtual std::string GetMeshFile() = 0;
	virtual std::string GetTextureFile() = 0;

	void SetApplication(Application* _app) { m_application = _app; }

	static Window* GetWindowInstance() { return m_window; }

protected:
	Window(int _screenWidth, int _screenHeight);
	~Window();

	int m_screenWidth;
	int m_screenHeight;

	Application* m_application;

private:

	static Window* m_window;
};