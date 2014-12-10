/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <gl\gl.h>


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcVertexBuffer.h"


namespace TgcViewer
{



/**
* A OpenGL vertex buffer
*/
class TgcOpenGLVertexBuffer : public TgcVertexBuffer
{

public:

	//Virtual members
	bool internalCreate(const void* data);
	void internalDispose();
	void* map(BufferMap::Map mapOption);
	void unmap();
	void update(const void* data);

private:
	

public:

	/**
	* OpenGL buffer
	*/
	GLuint buffer;

private:

	

};




}