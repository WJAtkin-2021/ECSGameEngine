#pragma once
#include "Renderer.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"

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

	// Platform independent interfaces
	Window* m_window;
	Renderer* m_renderer;

	// Manager classes
	SceneManager m_sceneManager;
	ResourceManager m_resourceManager;

	// Scene camera
	Camera m_camera;
};