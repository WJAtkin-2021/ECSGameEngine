#pragma once
#include <vector>
#include <Windows.h>

#include "KeyCode_Windows.h"

// The user input system, should handle input from windows virtual keys, game pads and touchscreen input eventually
// For this assignment we'll just implement the windows virtual keys for user input

struct KeyState
{
	bool down = false;
	bool downThisFrame = false;
};

struct MouseState
{
	KeyState mouse1;
	KeyState mouse2;
	int mousePosX = 0;
	int mousePosY = 0;
};

class UserInput
{
public:

	UserInput();
	~UserInput();

	// Getters for key states
	static bool KeyDown(const KeyCode_Windows e_keyCode);
	static bool KeyHeld(const KeyCode_Windows e_keyCode);

	// Getters for the mouse button state
	static bool GetMouse1Down() { return m_instance->m_mouseState.mouse1.downThisFrame; }
	static bool GetMouse2Down() { return m_instance->m_mouseState.mouse2.downThisFrame; }
	static bool GetMouse1Held() { return m_instance->m_mouseState.mouse1.down; }
	static bool GetMouse2Held() { return m_instance->m_mouseState.mouse2.down; }

	// Getters for the mouse cursor position
	static int GetMouseX() { return m_instance->m_mouseState.mousePosX; }
	static int GetMouseY() { return m_instance->m_mouseState.mousePosY; }

	// Called by the window class to process key inputs
	static void ProcKeyDown(const WPARAM _wParam);
	static void ProcKeyUp(const WPARAM _wParam);
	static void ProcMouseBtnDown(const WPARAM _wParam, const LPARAM _lParam);
	static void ProcMouseBtnUp(const int _button, const LPARAM _lParam);
	static void ProcMouseMove(const LPARAM _lParam);

	// Called by the game class
	static void NextFrame();
	static void ResetKeyPresses();

private:

	// Static instance so that this class can be used without a
	// pointer or reference to it
	static UserInput* m_instance;

	// Arrays for storing keyboard and mouse input
	std::vector<KeyState> m_keyStates;
	MouseState m_mouseState;
};