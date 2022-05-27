// Define and includes for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdexcept>

#include "Sandbox.h"

// Sandbox Settings
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	try
	{
		// Create and run the sandbox application
		Sandbox application(SCREEN_WIDTH, SCREEN_HEIGHT, hInstance);
	}
	catch(std::exception ex) 
	{ 
		// Display a warning box with the error
		const std::string errorString = ex.what();
		const LPWSTR longString = new wchar_t[errorString.size() + 1];
		std::copy(errorString.begin(), errorString.end(), longString);
		longString[errorString.size()] = 0;
		MessageBox(0, longString, L"Fatal Error", MB_ICONERROR | MB_OK);
	}


	// Dump memory leaks to the output
	_CrtDumpMemoryLeaks();
	return 0;
}