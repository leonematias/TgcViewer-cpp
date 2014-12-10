/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <windows.h>
#include <windowsx.h>

//Project Includes:
#include "TgcViewer/Window/TgcWindowHandler.h"




namespace TgcViewer
{

/**
* Windows implementation for TgcWindowHandler
*/
class Win32WindowHandler : public TgcWindowHandler
{

public:

	Win32WindowHandler();
	Win32WindowHandler(const Win32WindowHandler&);
	~Win32WindowHandler();
	
	//Virtual members
	void initializeWindow(GuiControllerConfig config);
	void run();
	void stop();
	void closeWindow();
	void resetTimer();
	void updateTimer();
	string getCurrentDir();
	void showErrorMessageBox(string title, string text);


	/**
	* {Internal}
	* Map each keyboard key to TgcInput values
	*/
	void initKeyboardMapping();

	/**
	* {Internal}
	* HighResolutionTimer functions
	*/ 
	long ticks();
	long frequency();

private:

	

public:

	/**
	* Window handler
	*/
	HWND hwnd;

	/**
	* Application name
	*/
	LPCSTR applicationName;

	/**
	* Application instance
	*/
	HINSTANCE hinstance;

	/**
	* GDI device context
	*/
	HDC deviceContext;



	/**
	* Running flag
	*/
	bool running;

	/**
	* Mapping for windows keyboard
	*/
	TgcInput::Keys KEYBOARD_MAPPINGS[255];


	/**
	* HighResolution timer values
	*/ 
	long startTime;
	int frameCount;
	float frameSecond;

private:

	

};

}


//Windows event handler
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);




