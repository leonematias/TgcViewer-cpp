/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/Renderer/OpenGL/TgcOpenGLRenderer.h"
using namespace TgcViewer;


TgcOpenGLRenderer::TgcOpenGLRenderer() : TgcRenderer()
{
	this->vsync = true;
	this->screenFarDistance = 10000;
	this->screenNearDistance = 1;
}


TgcOpenGLRenderer::TgcOpenGLRenderer(const TgcOpenGLRenderer& other)
{
}


TgcOpenGLRenderer::~TgcOpenGLRenderer()
{
}

bool TgcOpenGLRenderer::init()
{
	//Create context
	if(!(this->renderingContext = wglCreateContext(GuiController::Instance->windowHandler->deviceContext)))
	{
		GuiController::Instance->logger->logError("OpenGL creation error: wglCreateContext()");
		return false;
	}
	
	//Set context as current
	if(!wglMakeCurrent(GuiController::Instance->windowHandler->deviceContext, this->renderingContext))
	{
		GuiController::Instance->logger->logError("OpenGL creation error: wglMakeCurrent()");
		return false;
	}
	
	
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	//Back face culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Setup the projection matrix.
	this->fieldOfView = FastMath::PI / 4.0f;
	this->screenAspect = (float)GuiController::Instance->windowHandler->screenWidth / (float)GuiController::Instance->windowHandler->screenHeight;
	this->projectionMatrix = Matrix4::SPerspectiveFovLH(this->fieldOfView, this->screenAspect, this->screenNearDistance, this->screenFarDistance);

	//View matrix
	this->viewMatrix = Matrix4::SIdentity();


    return true;
}


void TgcOpenGLRenderer::shutdown()
{
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(this->renderingContext);
}	


void TgcOpenGLRenderer::beginScene()
{
	// Clear the back buffer and depth buffer.
	glClearColor(this->backgroundColor.R, this->backgroundColor.G, this->backgroundColor.B, this->backgroundColor.A);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void TgcOpenGLRenderer::endScene()
{
	SwapBuffers(GuiController::Instance->windowHandler->deviceContext);	
}


void TgcOpenGLRenderer::setVertexBuffer(const TgcVertexBuffer* vbuffer, unsigned int slot, unsigned int offset)
{
	TgcOpenGLVertexBuffer* glVbuffer = (TgcOpenGLVertexBuffer*)vbuffer;
	TgcOpenGLInputLayout* glInlayout = (TgcOpenGLInputLayout*)glVbuffer->inputLayout;

	glBindBuffer(GL_ARRAY_BUFFER, glVbuffer->buffer);
	glInlayout->setVertexAttribPointers();
}

void TgcOpenGLRenderer::setIndexBuffer(const TgcIndexBuffer* ibuffer, unsigned int offset)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((TgcOpenGLIndexBuffer*)ibuffer)->buffer);
}

void TgcOpenGLRenderer::drawIndexed(PrimitiveTopology::Topology topology, unsigned int indexCount, unsigned int startIndexLocation)
{
	glDrawElements(this->getPrimitiveTopology(topology), indexCount, GL_UNSIGNED_SHORT, (void*)startIndexLocation);
}

GLenum TgcOpenGLRenderer::getPrimitiveTopology(PrimitiveTopology::Topology topology)
{
	GLenum glTopology;
	switch(topology)
	{
		case PrimitiveTopology::TriangleList:
			glTopology = GL_TRIANGLES;
			break;
		case PrimitiveTopology::TriangleStrip:
			glTopology = GL_TRIANGLE_STRIP;
			break;
		case PrimitiveTopology::LineList:
			glTopology = GL_LINES;
			break;
		case PrimitiveTopology::LineStrip:
			glTopology = GL_LINE_STRIP;
			break;
		case PrimitiveTopology::PointList:
			glTopology = GL_POINTS;
			break;
	}
	return glTopology;
}

void TgcOpenGLRenderer::draw(PrimitiveTopology::Topology topology, unsigned int vertexCount, unsigned int startVertexLocation)
{
	glDrawArrays(this->getPrimitiveTopology(topology), startVertexLocation, vertexCount);
}




TgcTexture* TgcOpenGLRenderer::createTgcTextureInstance()
{
	return new TgcOpenGLTexture();
}

TgcVertexBuffer* TgcOpenGLRenderer::createTgcVertexBufferInstance()
{
	return new TgcOpenGLVertexBuffer();
}

TgcIndexBuffer* TgcOpenGLRenderer::createTgcIndexBufferInstance()
{
	return new TgcOpenGLIndexBuffer();
}

TgcInputLayout* TgcOpenGLRenderer::createTgcInputLayoutInstance()
{
	return new TgcOpenGLInputLayout();
}

TgcEffect* TgcOpenGLRenderer::createTgcEffectInstance()
{
	return new TgcOpenGLEffect();
}

TgcShaders* TgcOpenGLRenderer::createTgcShadersInstance()
{
	return new TgcOpenGLShaders();
}
