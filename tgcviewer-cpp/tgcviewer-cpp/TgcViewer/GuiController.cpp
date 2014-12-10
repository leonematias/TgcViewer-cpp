/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/GuiController.h"
using namespace TgcViewer;


GuiController* GuiController::Instance = NULL;


GuiController::GuiController()
{
	
}

GuiController::~GuiController()
{
}

void GuiController::newInstance()
{
	GuiController::Instance = new GuiController();
}

void GuiController::initGraphics(GuiControllerConfig config, TgcExample* example)
{
	this->currentExample = example;
	
	FastMath::init();
	
	//Init engine components
	this->renderer = TgcRendererFactory::createRenderer();
	this->windowHandler = this->renderer->createWindowHandler();
	this->windowHandler->initializeWindow(config);
	this->logger = new TgcLogger();
	string currentDir = this->windowHandler->getCurrentDir();
	this->examplesMediaPath = currentDir + "\\tgcviewer-cpp\\Media\\Examples\\";
	this->engineMediaPath = currentDir + "\\tgcviewer-cpp\\Media\\TgcViewer\\";
	this->renderer->init(config);
	this->input = new TgcInput();
	this->texturesPool = new TgcTexturePool();
	this->shaders = this->renderer->createTgcShadersInstance();
	this->shaders->loadCommonShaders();
	this->fontRenderer = new TgcFontRenderer();
	this->debugText = new TgcText2d();
	this->userVars = new TgcUserVars();
	this->gui = new TgcGui();
	this->modifiers = new TgcModifiers();

	//Init example
	this->windowHandler->resetTimer();
	this->currentExample->init();
	
	//Start the engine
	this->windowHandler->run();
}



void GuiController::render()
{
	this->renderer->beginScene();

	//Elapsed time
	this->windowHandler->updateTimer();
	this->elapsedTime = this->windowHandler->frameTime;
	int fps = this->windowHandler->fps;
	
	//Update input
	this->input->update();

	//Update modifiers
	this->modifiers->update();
	

	//Render example
	this->currentExample->render(elapsedTime);
	

	//Render modifiers
	this->modifiers->render();

	//Render fps
	this->drawText("FPS: " + TgcParserUtils::toString(fps), 2, 2);

	//Draw user vars
	this->userVars->render();
	

	this->renderer->endScene();
}

void GuiController::shutDown()
{
	this->windowHandler->stop();
}

void GuiController::dispose()
{
	this->currentExample->close();
	delete this->currentExample;

	delete this->input;
	
	this->renderer->shutdown();
	delete this->renderer;
	
	this->windowHandler->closeWindow();
	delete this->windowHandler;

	this->modifiers->dispose();
	delete this->modifiers;

	this->gui->dispose();
	delete this->gui;

	this->fontRenderer->dispose();
	delete this->fontRenderer;

	this->logger->dispose();
	delete this->logger;

	this->shaders->dispose();
	delete this->shaders;

	this->debugText->dispose();
	delete this->debugText;

	this->userVars->dispose();
	delete this->userVars;

	this->texturesPool->clearAll();
	delete this->texturesPool;

	delete GuiController::Instance;
}

void GuiController::drawText(string text, int x, int y, Color color)
{
	this->debugText->text = text;
	this->debugText->position = Vector2((float)x, (float)y);
	this->debugText->color = color;
	this->debugText->updateValues();
	this->debugText->render();
}
