#include "Sandbox.h"
#include "SandboxUI.h"
#include "ResourceManager.h"
#include "ComponentLoaderSandbox.h"

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

	// Pass our derived component loader to the engine's scene manager
	std::shared_ptr<ComponentLoaderEngine> compLoader = std::shared_ptr<ComponentLoaderEngine>(new ComponentLoaderSandbox());
	SceneManager::SetComponentLoader(compLoader);

	// Create the Sandbox UI class and pass it to the engine
	std::shared_ptr<ApplicationUI> sandboxUI = std::shared_ptr<ApplicationUI>(new SandboxUI());
	UI::SetApplicationUI(sandboxUI);

	SceneManager::OpenScene(m_defaultSceneFilepath);
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