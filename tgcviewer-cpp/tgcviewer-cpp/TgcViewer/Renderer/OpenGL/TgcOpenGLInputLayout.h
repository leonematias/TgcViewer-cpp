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
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcInputLayout.h"


namespace TgcViewer
{



/**
* OpenGL Input layout
*/
class TgcOpenGLInputLayout : public TgcInputLayout
{

public:

	//Virtual members
	void internalCreate();
	void dispose();

	/**
	* Calls glVertexAttribPointer() for each input element
	*/
	void setVertexAttribPointers();

private:


public:


private:

	
};




}