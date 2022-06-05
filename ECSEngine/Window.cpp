#include "Window.h"

Window* Window::m_window = nullptr;

Window::Window(int _screenWidth, int _screenHeight)
{
	m_window = this;

	m_screenWidth = _screenWidth;
	m_screenHeight = _screenHeight;
}

Window::~Window()
{

}

void Window::Loop()
{
	// Call the loop on the application class
	m_application->Update();
}