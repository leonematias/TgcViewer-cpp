/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/OpenGL/TgcOpenGLIndexBuffer.h"
using namespace TgcViewer;



bool TgcOpenGLIndexBuffer::internalCreate(const void* data)
{
	//OpenGL usage: http://www.opengl.org/sdk/docs/man/xhtml/glBufferData.xml
	GLenum glUsage;
	switch(this->usage)
	{
		case BufferUsage::Default:
			glUsage = GL_STATIC_DRAW;
			break;
		case BufferUsage::Dynamic:
			glUsage = GL_DYNAMIC_DRAW;
			break;
		case BufferUsage::Immutable:
			throw "TgcOpenGLIndexBuffer::internalCreate: BufferUsage::Immutable";
			break;
		case BufferUsage::Staging:
			throw "TgcOpenGLIndexBuffer::internalCreate: BufferUsage::Staging";
			break;
	}

	//Create and fill buffer
	glGenBuffers(1, &(this->buffer));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexSize * this->numVertices, data, glUsage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	return true;
}


void TgcOpenGLIndexBuffer::internalDispose()
{
	glDeleteBuffers(1, &(this->buffer));
}


