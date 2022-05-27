#pragma once
#include <Windows.h>
#include "Window.h"

class Window_Win : public Window
{
public:
	Window_Win(int _screenWidth, int _screenHeight, HINSTANCE _hInstance, int _nCmdShow);
	~Window_Win();

	void Init() override;
	void Loop() override;

private:

	// Callback function
	static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

	HWND m_hwnd = NULL;
};