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

	// Create the test entity
	Entity* testCube1 = SceneManager::CreateEntity();
	
}

void Sandbox::Update()
{
	// Call the Update on the base class
	Application::Update();
}