/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <windows.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library


//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcRenderer.h"
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLTexture.h"
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLVertexBuffer.h"
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLIndexBuffer.h"
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLInputLayout.h"
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLEffect.h"
#include "TgcViewer/Renderer/OpenGL/TgcOpenGLShaders.h"


namespace TgcViewer
{


/**
* Renderer for OpenGL
*/
class TgcOpenGLRenderer : public TgcRenderer
{

public:

	TgcOpenGLRenderer();
	TgcOpenGLRenderer(const TgcOpenGLRenderer&);
	~TgcOpenGLRenderer();


	//Virtual members
	bool init();
	void shutdown();
	void beginScene();
	void endScene();
	void setVertexBuffer(const TgcVertexBuffer* vbuffer, unsigned int slot = 0, unsigned int offset = 0);
	void setIndexBuffer(const TgcIndexBuffer* ibuffer, unsigned int offset = 0);
	void drawIndexed(PrimitiveTopology::Topology topology, unsigned int indexCount, unsigned int startIndexLocation = 0);
	void draw(PrimitiveTopology::Topology topology, unsigned int vertexCount, unsigned int startVertexLocation= 0);

	TgcTexture* createTgcTextureInstance();
	TgcVertexBuffer* createTgcVertexBufferInstance();
	TgcIndexBuffer* createTgcIndexBufferInstance();
	TgcInputLayout* createTgcInputLayoutInstance() ;
	TgcEffect* createTgcEffectInstance();
	TgcShaders* createTgcShadersInstance();



private:
	
	GLenum getPrimitiveTopology(PrimitiveTopology::Topology topology);

public:

	/**
	* Rendering context
	*/
	HGLRC renderingContext;
	
private:

	
};




}