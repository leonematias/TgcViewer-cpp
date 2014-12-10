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
#include "TgcViewer/Renderer/OpenGL/TextureLoader/soil.h"
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/TgcSceneLoader/TgcTexture.h"


namespace TgcViewer
{



/**
* An OpenGL Texture
*/
class TgcOpenGLTexture : public TgcTexture
{

public:

	//Virtual members
	void internalCreateFromFile();
	void internalDispose();



private:


public:

	/**
	* OpenGL texture ID
	*/
	GLuint glTextureId;

private:

	//TextureFormat::Format getTextureFormat(DXGI_FORMAT dxFormat);
	
};




}