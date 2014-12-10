/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/OpenGL/TgcOpenGLEffect.h"
using namespace TgcViewer;



void TgcOpenGLEffect::internalCreate()
{
	this->initialized = false;

	//Create vertex shader
	string vShaderPath = this->filePath + ".vs"
	string vShaderSource = TgcParserUtils::realAllText(vShaderPath);
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, (const GLchar**)&vShaderSource.c_str(), vShaderSource.length());
	glCompileShader(this->vertexShader);
	GLint shader_ok;
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) 
	{
		GuiController::Instance->logger->logError("Error loading OpenGL vertex shader, Path: " + vShaderPath + ", Error: " + getErrorMessage(this->vertexShader, glGetShaderiv, glGetShaderInfoLog));
        return;
    }

	//Create pixel shader
	string pShaderPath = this->filePath + ".ps"
	string pShaderSource = TgcParserUtils::realAllText(vShaderPath);
	this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->pixelShader, 1, (const GLchar**)&pShaderSource.c_str(), pShaderSource.length());
	glCompileShader(this->pixelShader);
	glGetShaderiv(this->pixelShader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) 
	{
		GuiController::Instance->logger->logError("Error loading OpenGL pixel shader, Path: " + pShaderPath + ", Error: " + getErrorMessage(this->pixelShader, glGetShaderiv, glGetShaderInfoLog));
        return;
    }


	//Create program and link
    this->program = glCreateProgram();
    glAttachShader(this->program, this->vertexShader);
    glAttachShader(this->program, this->pixelShader);
}


void TgcOpenGLEffect::init(const TgcVertexBuffer* vertexBuffer)
{
	if(!this->initialized)
	{
		TgcOpenGLInputLayout* inputLayout = ((TgcOpenGLInputLayout*)((TgcOpenGLVertexBuffer*)vertexBuffer)->inputLayout);

		//Attributes binding
		for(unsigned int i = 0; i < this->elements.size(); i++)
		{
			InputElement::Element element = this->elements[i];
			glBindAttributeLocation(this->program, i, element.name);
		}

		//Link after binding
		glLinkProgram(this->program);
		GLint program_ok;
		glGetProgramiv(this->program, GL_LINK_STATUS, &program_ok);
		if (!program_ok) {
			GuiController::Instance->logger->logError("Error linking shader in OpenGL, Path: " + this->filePath + ", Error: " + getErrorMessage(this->pixelShader, glGetProgramiv, glGetProgramInfoLog));
			glDeleteProgram(this->program);
			return;
		}
	}
}


void TgcOpenGLEffect::internalAddSampler(TgcEffectValues::Sampler sampler)
{
	GLint textureId = glGetUniformLocation(this->program, sampler.textureName);
	this->glSampleIds[sampler.textureName] = textureId;
}


void TgcOpenGLEffect::internalAddConstantBuffer(TgcEffectValues::ConstantBuffer constantBuffer)
{
	GLuint blockIndex = glGetUniformBlockIndex(this->program, constantBuffer.name);
	glUniformBlockBinding(this->program, blockIndex, constantBuffer.slot);

	GLuint glBuffer;
	glGenBuffers(1, &glBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, glBuffer);
 
	glBufferData(GL_UNIFORM_BUFFER, constantBuffer.size, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, constantBuffer.slot, glBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, NULL);

	glConstantBufferIds[constantBuffer.name] = glBuffer;
}


string TgcOpenGLEffect::getErrorMessage(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
    GLint log_length;
    glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
    char* log = new char[log_length];
    glGet__InfoLog(object, log_length, NULL, log);
	string error = log;
    delete log;
	return error;
}

/*
D3D10_FILTER TgcOpenGLEffect::getFilter(TgcEffectValues::Filter filter)
{
	switch(filter)
	{
	case TgcEffectValues::MinMagMipPoint:
		return D3D10_FILTER_MIN_MAG_MIP_POINT;
	case TgcEffectValues::MinMagMipLinear:
		return D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	case TgcEffectValues::Anisotropic:
		return D3D10_FILTER_ANISOTROPIC;
	}

	return D3D10_FILTER_MIN_MAG_MIP_LINEAR;
}

D3D10_TEXTURE_ADDRESS_MODE TgcOpenGLEffect::getAddressMode(TgcEffectValues::AddressMode addressMode)
{
	switch(addressMode)
	{
	case TgcEffectValues::Wrap:
		return D3D10_TEXTURE_ADDRESS_WRAP;
	case TgcEffectValues::Mirror:
		return D3D10_TEXTURE_ADDRESS_MIRROR;
	case TgcEffectValues::Border:
		return D3D10_TEXTURE_ADDRESS_BORDER;
	case TgcEffectValues::Clamp:
		return D3D10_TEXTURE_ADDRESS_CLAMP;
	case TgcEffectValues::MirrorOnce:
		return D3D10_TEXTURE_ADDRESS_MIRROR_ONCE;
	}

	return D3D10_TEXTURE_ADDRESS_WRAP;
}
*/

void TgcOpenGLEffect::begin()
{
	glUseProgram(this->program);

	/* enable attr
	for(var i = 0; i < this.attributes.length; i++) {
            gl.enableVertexAttribArray(this.attributes[i].pos);
    }
	*/
}

void TgcOpenGLEffect::end()
{
	glUseProgram(NULL);
}


void TgcOpenGLEffect::setTexture(string name, const TgcTexture* texture)
{
	TgcEffectValues::Sampler sampler = this->samplers[name];
	GLint glSamplerId = this->glSampleIds[name];
	TgcOpenGLTexture* glTexture = (TgcOpenGLTexture*)texture;

	//Texture slot
	GLenum glTextureSlot;
	switch(sampler.slot)
	{
	case 0:
		glTextureSlot = GL_TEXTURE0;
	case 1:
		glTextureSlot = GL_TEXTURE1;
	case 2:
		glTextureSlot = GL_TEXTURE2;
	case 3:
		glTextureSlot = GL_TEXTURE3;
	case 4:
		glTextureSlot = GL_TEXTURE4;
	case 5:
		glTextureSlot = GL_TEXTURE5;
	case 6:
		glTextureSlot = GL_TEXTURE6;
	case 7:
		glTextureSlot = GL_TEXTURE7;
	default:
		throw "Unsupported texture slot";
	}

	//Set texture
	glActiveTexture(glTextureSlot);
	glBindTexture(GL_TEXTURE_2D, glTexture->glTextureId);
	glUniform1i(glSamplerId, sampler.slot);
}

void TgcOpenGLEffect::setConstantBuffer(string name, const void* bufferData)
{
	TgcEffectValues::ConstantBuffer cBuffer = this->constantBuffers[name];
	GLuint glBuffer = this->glConstantBufferIds[name];

	glBindBuffer(GL_UNIFORM_BUFFER, glBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 , cBuffer.size, bufferData);
	//glBindBuffer(GL_UNIFORM_BUFFER, NULL);
}



void TgcOpenGLEffect::dispose()
{
	//Constant buffers
	for (unordered_map<string, GLuint>::iterator it = this->glConstantBufferIds.begin(); it != this->glConstantBufferIds.end(); ++it) 
	{
		GLuint cBuffer = it->second;
		glDeleteBuffers(1, &cBuffer);
	}

	//Sampler states
	for (unordered_map<string, GLint>::iterator it = this->glSampleIds.begin(); it != this->glSampleIds.end(); ++it) 
	{
		GLint sampler = it->second;
		glDeleteTextures(1, &sampler);
	}

	//program
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->pixelShader);
	glDeleteProgram(this->program);
}


