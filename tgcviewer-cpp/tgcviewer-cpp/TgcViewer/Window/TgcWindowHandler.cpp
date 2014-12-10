/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/Window/TgcWindowHandler.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;



TgcWindowHandler::TgcWindowHandler()
{
	this->fullScreen = false;
	this->frameTime = 0;
	this->fps = 0;
}


TgcWindowHandler::TgcWindowHandler(const TgcWindowHandler& other)
{
}


TgcWindowHandler::~TgcWindowHandler()
{
}
