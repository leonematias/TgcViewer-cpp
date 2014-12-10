/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/OpenGL/TgcOpenGLTexture.h"
using namespace TgcViewer;


void TgcOpenGLTexture::internalCreateFromFile()
{
	/*
	//Create texture form file
	//glLOAD(this->filePath.c_str());
	glGenTextures(1, &this->glTextureId);
	glBindTexture(GL_TEXTURE_2D, textureid);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, your_data);
	*/

	//Load image from file
	int soilChannels;
	unsigned char* imageData = SOIL_load_image(this->filePath.c_str(), &this->width, &this->height, &soilChannels, SOIL_LOAD_AUTO);
	if(imageData == NULL)
	{
		GuiController::Instance->logger->logError("Could not load image from file: " + this->fileName + ", Path: " + this->filePath);
		return;
	}

	//Create OpenGL texture
	this->glTextureId = SOIL_load_OGL_texture_from_memory(imageData, this->width * this->height, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	if(this->glTextureId == 0)
	{
		GuiController::Instance->logger->logError("Could not create OpenGL texture: " + this->fileName + ", Path: " + this->filePath);
		return;
	}

	//Format
	switch(soilChannels)
	{
	case SOIL_LOAD_RGB:
		//TODO check this format
		this->format = TextureFormat::R8G8B8A8_UNORM;
		break;
	case SOIL_LOAD_RGBA:
		this->format = TextureFormat::R8G8B8A8_UNORM;
		break;
	}





	/*
	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the original
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// the texture wraps over at the edges (repeat)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	*/

	
}


void TgcOpenGLTexture::internalDispose()
{
	glDeleteTextures(1, &this->glTextureId);
}

/*
TextureFormat::Format TgcOpenGLTexture::getTextureFormat(DXGI_FORMAT dxFormat)
{
	switch(dxFormat)
	{
	//Common case
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		return TextureFormat::R8G8B8A8_UNORM;

	case DXGI_FORMAT_R8_UINT:
		return TextureFormat::R8_UINT;
	case DXGI_FORMAT_R8_SINT:
		return TextureFormat::R8_SINT;
	case DXGI_FORMAT_R8_UNORM:
		return TextureFormat::R8_UNORM;
	case DXGI_FORMAT_R16_UINT:
		return TextureFormat::R16_UINT;
	case DXGI_FORMAT_R16_SINT:
		return TextureFormat::R16_SINT;
	case DXGI_FORMAT_R16_UNORM:
		return TextureFormat::R16_UNORM;
	case DXGI_FORMAT_R16_FLOAT:
		return TextureFormat::R16_FLOAT;
	case DXGI_FORMAT_R8G8_UINT:
		return TextureFormat::R8G8_UINT;
	case DXGI_FORMAT_R8G8_SINT:
		return TextureFormat::R8G8_SINT;
	case DXGI_FORMAT_R8G8_UNORM:
		return TextureFormat::R8G8_UNORM;
	case DXGI_FORMAT_R32_UINT:
		return TextureFormat::R32_UINT;
	case DXGI_FORMAT_R32_SINT:
		return TextureFormat::R32_SINT;
	case DXGI_FORMAT_R32_FLOAT:
		return TextureFormat::R32_FLOAT;
	case DXGI_FORMAT_R16G16_UINT:
		return TextureFormat::R16G16_UINT;
	case DXGI_FORMAT_R16G16_SINT:
		return TextureFormat::R16G16_SINT;
	case DXGI_FORMAT_R16G16_UNORM:
		return TextureFormat::R16G16_UNORM;
	case DXGI_FORMAT_R16G16_FLOAT:
		return TextureFormat::R16G16_FLOAT;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		return TextureFormat::R8G8B8A8_UINT;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		return TextureFormat::R8G8B8A8_SINT;
	case DXGI_FORMAT_R32G32_UINT:
		return TextureFormat::R32G32_UINT;
	case DXGI_FORMAT_R32G32_SINT:
		return TextureFormat::R32G32_SINT;
	case DXGI_FORMAT_R32G32_FLOAT:
		return TextureFormat::R32G32_FLOAT;
	case DXGI_FORMAT_R32G32B32_UINT:
		return TextureFormat::R32G32B32_UINT;
	case DXGI_FORMAT_R32G32B32_SINT:
		return TextureFormat::R32G32B32_SINT;
	case DXGI_FORMAT_R32G32B32_FLOAT:
		return TextureFormat::R32G32B32_FLOAT;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		return TextureFormat::R16G16B16A16_UINT;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		return TextureFormat::R16G16B16A16_SINT;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		return TextureFormat::R16G16B16A16_UNORM;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		return TextureFormat::R16G16B16A16_FLOAT;
	case DXGI_FORMAT_R32G32B32A32_UINT:
		return TextureFormat::R32G32B32A32_UINT;
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return TextureFormat::R32G32B32A32_SINT;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		return TextureFormat::R32G32B32A32_FLOAT;
	}
	return TextureFormat::R8G8B8A8_UNORM;
}
*/
