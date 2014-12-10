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
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiControllerConfig.h"
#include "TgcViewer/Input/TgcInput.h"
#include "TgcViewer/Math/Vector2.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;};




namespace TgcViewer
{

/**
* An abstract Window Handler to interact with the platform-dependent 
* window system, the input system, high resolution time and filesystem.
* Each specific platform must extend this class.
*/
class TgcWindowHandler
{

public:

	TgcWindowHandler();
	TgcWindowHandler(const TgcWindowHandler&);
	~TgcWindowHandler();
	
	/**
	* Create a new window
	*/
	virtual void initializeWindow(GuiControllerConfig config) = 0;

	/**
	* Run events and starts the main loop.
	* It must invoke GuiController::Instance->render() and feed 
	* GuiController::Instance->input with the input data.
	*/
	virtual void run() = 0;
	
	/**
	* Stops the main loop
	*/
	virtual void stop() = 0;

	/**
	* Close the window and free resources
	*/
	virtual void closeWindow() = 0;

	/**
	* Reset the values of the timer for frameTime and fps
	*/
	virtual void resetTimer() = 0;

	/**
	* Compute timer values for frameTime and fps
	*/
	virtual void updateTimer() = 0;

	/**
	* Returns the directory of the application's executable file
	*/
	virtual string getCurrentDir() = 0;

	/**
	* Shows an alert box with an error
	*/
	virtual void showErrorMessageBox(string title, string text) = 0;



	/**
	* Window size
	*/
	inline Vector2 size() const {return Vector2((float)screenWidth, (float)screenHeight);}

private:

public:

	/**
	* Screen width
	*/
	int screenWidth;

	/**
	* Screen height
	*/
	int screenHeight;

	/**
	* True if the windows is running in full-screen mode
	*/
	bool fullScreen;

	/**
	* The time elapsed between frames (in seconds)
	*/
	float frameTime;

	/**
	* Frames per second
	*/
	int fps;

private:

	

};

}


