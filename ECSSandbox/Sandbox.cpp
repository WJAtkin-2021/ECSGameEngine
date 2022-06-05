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
	// Call init on the base class first
	Application::Init();

	// Create the Sandbox UI class and pass it to the engine
	std::shared_ptr<ApplicationUI> sandboxUI = std::shared_ptr<ApplicationUI>(new SandboxUI());
	UI::SetApplicationUI(sandboxUI);

	// Set the camera
	m_camera.GetTransform().SetPosition(Vector3D(0.0f, 1.0f, -10.0f));

	// Create the test entity
	Entity* testCube1 = SceneManager::CreateEntity();
	testCube1->GetComponent<Transform>()->SetPosition(Vector3D(0.0f, 0.0f, 0.0f));
	testCube1->SetName("Test Cube");
	RenderComponent* testRender = testCube1->AddComponent<RenderComponent>();
	testRender->SetMesh(ResourceManager::GetMesh(PrimitiveTypes::Cube));
}

void Sandbox::Update()
{
	// Call the Update on the base class
	Application::Update();
}