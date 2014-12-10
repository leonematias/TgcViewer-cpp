/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/TgcLogger.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcLogger::TgcLogger()
{
}


TgcLogger::TgcLogger(const TgcLogger& other)
{
}


TgcLogger::~TgcLogger()
{
}

void TgcLogger::log(string txt)
{
	cout << txt;
}

void TgcLogger::logError(string txt)
{
	cerr << txt;
	GuiController::Instance->windowHandler->showErrorMessageBox("Error", txt);
}

void TgcLogger::dispose()
{
}

