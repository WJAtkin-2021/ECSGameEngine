#include "Application.h"
#include "Renderer_DX11.h"
#include "Window_Win.h"

Application::Application(Window* _window, int _screenWidth, int _screenHeight)
{
	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;
	m_window = _window;

	// Setup the renderer
	// TODO: Make use of pre-processor commands for determining the correct platform
	Renderer_DX11* renderer = new Renderer_DX11();
	Window_Win* window = dynamic_cast<Window_Win*>(_window);
	renderer->SetWindowsHandle(window->GetHandle());
	m_renderer = dynamic_cast<Renderer*>(renderer);
	m_renderer->InitGraphicsAPI(m_screenWidth, m_screenHeight);

	// Pass the application class to the window class
	_window->SetApplication(this);
}

Application::~Application()
{
	delete m_renderer;
}

void Application::Init()
{

}

void Application::Update()
{

	// Draw the scene
	m_renderer->DrawScene();
}