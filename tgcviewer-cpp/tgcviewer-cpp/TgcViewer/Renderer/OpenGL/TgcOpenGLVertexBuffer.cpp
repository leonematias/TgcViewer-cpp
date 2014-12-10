/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/OpenGL/TgcOpenGLVertexBuffer.h"
using namespace TgcViewer;



bool TgcOpenGLVertexBuffer::internalCreate(const void* data)
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
			throw "TgcOpenGLVertexBuffer::internalCreate: BufferUsage::Immutable";
			break;
		case BufferUsage::Staging:
			throw "TgcOpenGLVertexBuffer::internalCreate: BufferUsage::Staging";
			break;
	}

	//Create and fill buffer
	glGenBuffers(1, &(this->buffer));
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexSize * this->numVertices, data, glUsage);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	return true;
}

void TgcOpenGLVertexBuffer::internalDispose()
{
	glDeleteBuffers(1, &(this->buffer));
}


void* TgcOpenGLVertexBuffer::map(BufferMap::Map mapOption)
{
	if(this->usage != BufferUsage::Dynamic)
	{
		GuiController::Instance->logger->logError("The vertexBuffer is not dynamic and cannot be mapped");
		return NULL;
	}

	//OpenGL map
	GLbitfield access​;
	switch(mapOption)
	{
		case BufferMap::Read:
			access​ = GL_MAP_READ_BIT;
			break;
		case BufferMap::Write:
			access​ = GL_MAP_WRITE_BIT;
			break;
		case BufferMap::ReadWrite:
			access​ = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
			break;
		case BufferMap::WriteDiscard:
			access​ = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
			break;
		case BufferMap::WriteNoOverwrite:
			throw "TgcOpenGLVertexBuffer::map: BufferMap::WriteNoOverwrite";
			break;
	}

	//Map vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	void* data = glMapBufferRange(GL_ARRAY_BUFFER, 0, this->vertexSize * this->numVertices, access​);

	return data;
}


void TgcOpenGLVertexBuffer::unmap()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void TgcOpenGLVertexBuffer::update(const void* data)
{
	if(this->usage != BufferUsage::Dynamic)
	{
		GuiController::Instance->logger->logError("The vertexBuffer is not dynamic and cannot be updated");
		return NULL;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
	glBufferSubData​(GL_ARRAY_BUFFER, 0, this->vertexSize * this->numVertices, data);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}
