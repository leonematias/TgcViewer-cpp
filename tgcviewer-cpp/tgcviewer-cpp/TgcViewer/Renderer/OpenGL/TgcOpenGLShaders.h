/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Shaders/TgcShaders.h"
#include "TgcViewer/GuiController.h"


namespace TgcViewer
{



/**
* OpenGL common engine shader effects
*/
class TgcOpenGLShaders : public TgcShaders
{

public:


	//Virtual members
	void loadCommonShaders();
	void dispose();


private:
	
public:


private:

	
};




}