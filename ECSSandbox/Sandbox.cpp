#include "Sandbox.h"
#include "SandboxUI.h"

Sandbox::Sandbox(Window* _window, int _screenWidth, int _screenHeight) : Application(_window, _screenWidth, _screenHeight)
{

}

Sandbox::~Sandbox()
{

}

void Sandbox::Init()
{
	// Create the Sandbox UI class and pass it to the engine
	std::shared_ptr<ApplicationUI> sandboxUI = std::shared_ptr<ApplicationUI>(new SandboxUI());
	UI::SetApplicationUI(sandboxUI);
}

void Sandbox::Update()
{


	// Call the Update on the base class
	Application::Update();
}