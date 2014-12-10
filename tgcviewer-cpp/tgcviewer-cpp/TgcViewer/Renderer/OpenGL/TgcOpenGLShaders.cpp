/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Renderer/OpenGL/TgcOpenGLShaders.h"
using namespace TgcViewer;



void TgcOpenGLShaders::loadCommonShaders()
{
	string shadersPath = GuiController::Instance->engineMediaPath + "Shaders\\OpenGL\\";
	TgcEffectValues::Description desc;

	//tgcMeshShaderVertexColor
	this->tgcMeshShaderVertexColor = TgcEffect::createFromFile(shadersPath + "TgcMeshShader_VertexColor", "main", "main");
	this->tgcMeshShaderVertexColor->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));

	//tgcMeshShaderDiffuseMap
	this->tgcMeshShaderDiffuseMap = TgcEffect::createFromFile(shadersPath + "TgcMeshShader_DiffuseMap", "main", "main");
	this->tgcMeshShaderDiffuseMap->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));
	this->tgcMeshShaderDiffuseMap->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));

	//tgcMeshShaderDiffuseMap
	this->tgcMeshShaderDiffuseMapAndLightmap = TgcEffect::createFromFile(shadersPath + "TgcMeshShader_DiffuseMapAndLightmap", "main", "main");
	this->tgcMeshShaderDiffuseMapAndLightmap->addConstantBuffer(TgcEffectValues::ConstantBuffer("MatrixBuffer", TgcEffectValues::VS_AND_PS, sizeof(TgcShadersCommon::MatrixBuffer), 0));
	this->tgcMeshShaderDiffuseMapAndLightmap->addSampler(TgcEffectValues::Sampler("diffuseMap", "texDiffuseMap",TgcEffectValues::PS, 0));
	this->tgcMeshShaderDiffuseMapAndLightmap->addSampler(TgcEffectValues::Sampler("lightMap", "texLightMap",TgcEffectValues::PS, 1));
}

void TgcOpenGLShaders::dispose()
{
	if(this->tgcMeshShaderVertexColor)
	{
		this->tgcMeshShaderVertexColor->dispose();
		this->tgcMeshShaderVertexColor = 0;
	}
	if(this->tgcMeshShaderDiffuseMap)
	{
		this->tgcMeshShaderDiffuseMap->dispose();
		this->tgcMeshShaderDiffuseMap = 0;
	}
	if(this->tgcMeshShaderDiffuseMapAndLightmap)
	{
		this->tgcMeshShaderDiffuseMapAndLightmap->dispose();
		this->tgcMeshShaderDiffuseMapAndLightmap = 0;
	}
}