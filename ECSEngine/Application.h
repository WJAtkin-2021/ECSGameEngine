#pragma once

class Application
{
public:
	Application(int _screenWidth, int _screenHeight);
	~Application();

	virtual void Init();
	virtual void Loop();

protected:
	int m_screenWidth;
	int m_screenHeight;
};