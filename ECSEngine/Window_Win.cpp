#include "Window_Win.h"

Window_Win::Window_Win(int _screenWidth, int _screenHeight, HINSTANCE _hInstance, int _nCmdShow) : Window(_screenWidth, _screenHeight)
{
	// Register the window
	const wchar_t className[] = L"ECSEngineWindow";

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Window_Win::WindowProc;
	wc.hInstance = _hInstance;
	wc.lpszClassName = className;

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, _screenWidth, _screenHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the window
	m_hwnd = CreateWindowEx(NULL,
		className,
		L"ECS Engine",
		WS_OVERLAPPEDWINDOW,
		300,
		150,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		_hInstance,
		NULL);

	// Check if the window was created
	if (m_hwnd == NULL)
	{
		// TODO: Throw error message
	}
	else
	{
		ShowWindow(m_hwnd, _nCmdShow);
	}
}

Window_Win::~Window_Win()
{

}

void Window_Win::Init()
{

}

void Window_Win::Loop()
{
	// Run the message loop
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// Handle any messages if any are waiting
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise update the game
		else
		{
			// Call the loop on the base class
			Window::Loop();
		}
	}
}

LRESULT CALLBACK Window_Win::WindowProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(_hwnd, _uMsg, _wParam, _lParam);
}