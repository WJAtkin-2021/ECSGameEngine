#pragma once

class Window
{
public:

	virtual void Init() = 0;
	virtual void Loop();

protected:
	Window(int _screenWidth, int _screenHeight);
	~Window();

	int m_screenWidth;
	int m_screenHeight;
};