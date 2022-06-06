#include "Sandbox.h"
#include "SandboxUI.h"
#include "ResourceManager.h"

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
	ProcessKeyInput();

	// Call the Update on the base class
	Application::Update();
}

void Sandbox::ProcessKeyInput()
{
	// Camera Z
	if (UserInput::KeyHeld(KeyCode_Windows::Key_W))
	{
		m_camera.GetTransform().MoveLocalZ(5.0f * Time::DeltaTime());
	}
	else if (UserInput::KeyHeld(KeyCode_Windows::Key_S))
	{
		m_camera.GetTransform().MoveLocalZ(-5.0f * Time::DeltaTime());
	}
	// X axis
	if (UserInput::KeyHeld(KeyCode_Windows::Key_D))
	{
		m_camera.GetTransform().MoveLocalX(5.0f * Time::DeltaTime());
	}
	else if (UserInput::KeyHeld(KeyCode_Windows::Key_A))
	{
		m_camera.GetTransform().MoveLocalX(-5.0f * Time::DeltaTime());
	}
	// Y axis
	if (UserInput::KeyHeld(KeyCode_Windows::Key_E))
	{
		m_camera.GetTransform().MoveLocalY(5.0f * Time::DeltaTime());
	}
	else if (UserInput::KeyHeld(KeyCode_Windows::Key_Q))
	{
		m_camera.GetTransform().MoveLocalY(-5.0f * Time::DeltaTime());
	}

	// Rotate based on mouse movement
	if (UserInput::GetMouse2Held())
	{
		static int startMouseX = 0;
		static int startMouseY = 0;
		static float startCamY = 0.0f;
		static float startCamX = 0.0f;

		// Check to see if this is the first frame where the mouse button is held
		if (UserInput::GetMouse2Down())
		{
			startMouseX = UserInput::GetMouseX();
			startMouseY = UserInput::GetMouseY();
			startCamY = m_camera.GetTransform().Rotation().m_y;
			startCamX = m_camera.GetTransform().Rotation().m_x;
		}

		// Rotate the camera based on how far the mouse moved
		const int mouseXDelta = UserInput::GetMouseX() - startMouseX;
		const int mouseYDelta = UserInput::GetMouseY() - startMouseY;
		m_camera.GetTransform().SetRotY(startCamY + static_cast<float>(mouseXDelta) * m_camSensitivity);
		m_camera.GetTransform().SetRotX(startCamX + static_cast<float>(mouseYDelta) * m_camSensitivity);
	}
}