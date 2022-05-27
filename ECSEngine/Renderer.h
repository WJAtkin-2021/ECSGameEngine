#pragma once

class Renderer
{
public:
	virtual void InitGraphicsAPI(int _screenWidth, int _screenHeight) = 0;
	virtual void DrawScene() = 0;

protected:
	Renderer();
	~Renderer();

	int m_screenWidth;
	int m_screenHeight;
};