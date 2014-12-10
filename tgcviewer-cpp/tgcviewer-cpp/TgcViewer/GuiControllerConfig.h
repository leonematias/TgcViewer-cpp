/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once


//General Includes:
#include <string>
using namespace std;

//Project Includes:



namespace TgcViewer
{


/**
* Configuration for GuiController startup
*/
struct GuiControllerConfig
{
	bool fullscreen;
	int screenWidth;
	int screenHeight;
	string title;
	bool vsync;
	float screenNearDistance;
	float screenFarDistance;
};




}