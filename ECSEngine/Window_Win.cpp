#include <filesystem>
#include <iostream>
#include "imgui/backends/imgui_impl_win32.h"
#include "Window_Win.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window_Win* Window_Win::m_windowWin = nullptr;

Window_Win::Window_Win(int _screenWidth, int _screenHeight, HINSTANCE _hInstance, int _nCmdShow) : Window(_screenWidth, _screenHeight)
{
	m_windowWin = this;

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

std::string Window_Win::GetMeshFile()
{
	WCHAR szPath[MAX_PATH] = {};

	OPENFILENAME ofn = { sizeof(ofn) };
	ofn.hwndOwner = m_hwnd;
	ofn.lpstrFilter = L"OBJ Files (*.obj)\0*.obj\0";
	ofn.lpstrFile = szPath;
	ofn.nMaxFile = ARRAYSIZE(szPath);
	ofn.Flags = OFN_NOCHANGEDIR;

	const BOOL fOk = GetOpenFileName(&ofn);
	std::string relativePath;
	if (fOk)
	{
		// Decompose the path into a relative path
		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);
		std::filesystem::current_path(NPath);
		const std::filesystem::path filePath = std::filesystem::path(szPath);
		relativePath = std::filesystem::relative(filePath).generic_string();
	}

	// TOD: Reset the keys as the window lost focus
	//UserInput::ResetKeyPresses();
	return relativePath;
}

LRESULT CALLBACK Window_Win::WindowProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	// Check if this message was meant for Dear ImGui
	if (ImGui_ImplWin32_WndProcHandler(_hwnd, _uMsg, _wParam, _lParam))
		return true;

	switch (_uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(_hwnd, _uMsg, _wParam, _lParam);
}