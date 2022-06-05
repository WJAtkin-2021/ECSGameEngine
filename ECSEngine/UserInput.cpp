#include <windowsx.h> // Used for GET_X_LPARAM and GET_Y_LPARAM
#include "UserInput.h"

UserInput* UserInput::m_instance = nullptr;

UserInput::UserInput()
{
	m_instance = this;

	// Init the key state array
	for (int i = 0; i < 128; i++)
	{
		m_keyStates.push_back(KeyState());
	}
}

UserInput::~UserInput() { }

bool UserInput::KeyDown(const KeyCode_Windows e_keyCode)
{
	const size_t pos = static_cast<size_t>(e_keyCode);
	return m_instance->m_keyStates[pos].downThisFrame;
}

bool UserInput::KeyHeld(const KeyCode_Windows e_keyCode)
{
	const size_t pos = static_cast<size_t>(e_keyCode);
	return m_instance->m_keyStates[pos].down;
}

void UserInput::NextFrame()
{
	// Key states
	for (int i = 0; i < 128; i++)
	{
		m_instance->m_keyStates[i].downThisFrame = false;
	}

	// Mouse states
	m_instance->m_mouseState.mouse1.downThisFrame = false;
	m_instance->m_mouseState.mouse2.downThisFrame = false;
}

void UserInput::ProcKeyDown(const WPARAM _wParam)
{
	if (_wParam <= 128)
	{
		m_instance->m_keyStates[_wParam].down = true;
		m_instance->m_keyStates[_wParam].downThisFrame = true;
	}
}

void UserInput::ProcKeyUp(const WPARAM _wParam)
{
	if (_wParam <= 128)
	{
		m_instance->m_keyStates[_wParam].down = false;
	}
}

void UserInput::ProcMouseBtnDown(const WPARAM _wParam, const LPARAM _lParam)
{
	m_instance->m_mouseState.mousePosX = GET_X_LPARAM(_lParam);
	m_instance->m_mouseState.mousePosY = GET_Y_LPARAM(_lParam);

	if (_wParam == MK_LBUTTON)
	{
		m_instance->m_mouseState.mouse1.down = true;
		m_instance->m_mouseState.mouse1.downThisFrame = true;
	}
	else if (_wParam == MK_RBUTTON)
	{
		m_instance->m_mouseState.mouse2.down = true;
		m_instance->m_mouseState.mouse2.downThisFrame = true;
	}
}

void UserInput::ProcMouseBtnUp(const int _button, const LPARAM _lParam)
{
	m_instance->m_mouseState.mousePosX = GET_X_LPARAM(_lParam);
	m_instance->m_mouseState.mousePosY = GET_Y_LPARAM(_lParam);

	if (_button == 1)
	{
		m_instance->m_mouseState.mouse1.down = false;
	}
	else if (_button == 2)
	{
		m_instance->m_mouseState.mouse2.down = false;
	}
}

void UserInput::ProcMouseMove(const LPARAM _lParam)
{
	m_instance->m_mouseState.mousePosX = GET_X_LPARAM(_lParam);
	m_instance->m_mouseState.mousePosY = GET_Y_LPARAM(_lParam);
}

void UserInput::ResetKeyPresses()
{
	for (int i = 0; i < m_instance->m_keyStates.size(); i++)
	{
		m_instance->m_keyStates[i].down = false;
		m_instance->m_keyStates[i].downThisFrame = false;
	}
	m_instance->m_mouseState.mouse1.down = false;
	m_instance->m_mouseState.mouse2.down = false;
}