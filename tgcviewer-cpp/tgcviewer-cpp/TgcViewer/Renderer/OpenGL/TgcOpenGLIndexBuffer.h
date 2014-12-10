/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <windows.h>
#include <gl\gl.h>

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcIndexBuffer.h"


namespace TgcViewer
{



/**
* OpenGL Index Buffer
*/
class TgcOpenGLIndexBuffer : public TgcIndexBuffer
{

public:

	//Virtual members
	bool internalCreate(const void* data);
	void internalDispose();

private:


public:

	/**
	* OpenGL buffer
	*/
	GLuint buffer;

private:

	
};




}