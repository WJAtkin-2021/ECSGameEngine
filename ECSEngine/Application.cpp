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
	// Load in the shaders
#ifdef BUILD_DX_11
	ResourceManager::GetShader(ShaderType::Vertex_HLSL);
	//ResourceManager::GetShader(ShaderType::VertexSkyBox_HLSL);
	ResourceManager::GetShader(ShaderType::PixelFallBack_HLSL);
	//ResourceManager::GetShader(ShaderType::PixelTextured_HLSL);
	//ResourceManager::GetShader(ShaderType::PixelSkyBox_HLSL);
#elif BUILD_OpenGL
	ResourceManager::GetShader(ShaderType::Vertex_GLSL);
	ResourceManager::GetShader(ShaderType::VertexSkyBox_GLSL);
	ResourceManager::GetShader(ShaderType::FragmentFallBack_GLSL);
	ResourceManager::GetShader(ShaderType::FragmentTextured_GLSL);
	ResourceManager::GetShader(ShaderType::FragmentSkyBox_GLSL);
#endif // BUILD_DX_11

	// Set the screen size on the camera
	m_camera.SetWindowSize(m_screenWidth, m_screenHeight);
}

void Application::Update()
{

	// Draw the scene
	m_renderer->DrawScene();
}