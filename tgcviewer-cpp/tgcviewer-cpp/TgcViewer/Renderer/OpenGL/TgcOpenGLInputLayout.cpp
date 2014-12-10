/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/OpenGL/TgcOpenGLInputLayout.h"
using namespace TgcViewer;


void TgcOpenGLInputLayout::internalCreate()
{
	
}

void TgcOpenGLInputLayout::dispose()
{
	
}

void TgcOpenGLInputLayout::setVertexAttribPointers()
{
	unsigned int offset = 0;
	unsigned int size;
	for(unsigned int i = 0; i < this->elements.size(); i++)
	{
		//OpenGL type
		GLenum glType;
		switch(this->elements[i].type)
		{
		case InputElement::Float:
			glType = GL_FLOAT;
			break;
		case InputElement::Float2:
			glType = GL_FLOAT;
			break;
		case InputElement::Float3:
			glType = GL_FLOAT;
			break;
		case InputElement::Float4:
			glType = GL_FLOAT;
			break;
		case InputElement::UnsignedInt:
			glType = GL_UNSIGNED_INT;
			break;
		case InputElement::SignedInt:
			glType = GL_INT;
			break;
		}

		size = this->elements[i].size()
		glVertexAttribPointer(i, size, glType, false, this->size, (void*)offset);
		offset += size;
	}
}

