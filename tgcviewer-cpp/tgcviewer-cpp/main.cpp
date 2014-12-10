/*#############################################################
TgcViewer-cpp

Author: Matias Leone

Application entry point
#############################################################*/

#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/GuiControllerConfig.h"
#include "TgcViewer/Example/TgcExample.h"
using namespace TgcViewer; 


//Concret example to be used
#include "Examples/Example1/Example1.h"
#include "Examples/ExampleVB/ExampleVB.h"
#include "Examples/ExampleEditor/ExampleEditor.h"
#include "Examples/ExampleTgcBox/ExampleTgcBox.h"
#include "Examples/ExampleSprite/ExampleSprite.h"
#include "Examples/ExamplesUI/ExampleUI.h"
#include "Examples/ExamplesUI/ExampleModifier.h"
using namespace Examples; 


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	GuiControllerConfig config;
	config.fullscreen = false;
	config.screenWidth = 1024;
	config.screenHeight = 768;
	config.title = "TgcViewer";
	config.vsync = true;
	config.screenNearDistance = 0.1f;
	config.screenFarDistance = 1000.0f;

	//Create GuiController
	GuiController::newInstance();

	
	//Create concret example
	//TgcExample* example = new Example1();
	//TgcExample* example = new ExampleVB();
	//TgcExample* example = new ExampleEditor();
	TgcExample* example = new ExampleTgcBox();
	//TgcExample* example = new ExampleSprite();
	//TgcExample* example = new ExampleUI();
	//TgcExample* example = new ExampleModifier();
	
	
	//Init graphics
	GuiController::Instance->initGraphics(config, example);

	//Shutdown
	//GuiController::Instance->dispose();

	return 0;
}