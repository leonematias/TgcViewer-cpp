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
#include <unordered_map>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/GuiController.h"
#include "TgcViewer/Renderer/TgcEffect.h"
#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"


namespace TgcViewer
{



/**
* OpenGL Effect
*/
class TgcOpenGLEffect : public TgcEffect
{

public:


	//Virtual members
	void internalCreate();
	void internalAddSampler(TgcEffectValues::Sampler sampler);
	void internalAddConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer);
	void init(const TgcVertexBuffer* vertexBuffer);
	void begin();
	void setTexture(string name, const TgcTexture* texture);
	void setConstantBuffer(string name, const void* bufferData);
	void end();
	void dispose();



	//D3D10_FILTER TgcDX10Effect::getFilter(TgcEffectValues::Filter filter);
	//D3D10_TEXTURE_ADDRESS_MODE TgcDX10Effect::getAddressMode(TgcEffectValues::AddressMode addressMode);


private:

	string getErrorMessage(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);

public:

	/**
	* Vertex shader ID
	*/
	GLuint vertexShader;

	/**
	* Pixel shader ID
	*/
	GLuint pixelShader;

	/**
	* Shader program
	*/
	GLuint program;

	/**
	* Tell if the effect was already initialized
	*/
	bool initialized;

	/**
	* Sampler IDs map
	*/
	unordered_map<string, GLint> glSampleIds;

	/**
	* Constant buffers map
	*/
	unordered_map<string, GLuint> glConstantBufferIds;

private:

	
};




}