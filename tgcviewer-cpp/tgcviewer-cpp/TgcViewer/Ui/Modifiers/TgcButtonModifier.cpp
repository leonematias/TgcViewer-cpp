/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#include "TgcViewer/Ui/Modifiers/TgcButtonModifier.h"
#include "TgcViewer/GuiController.h" //required by forward declaration
using namespace TgcViewer;


TgcButtonModifier::TgcButtonModifier(const string id, const string label)
{
	this->init(id);
	
	button = new TgcGuiButton(id, label);
	GuiController::Instance->gui->add(button);

	this->size = button->size;
}

TgcButtonModifier::TgcButtonModifier(const TgcButtonModifier& other)
{
}

TgcButtonModifier::~TgcButtonModifier()
{
}

void TgcButtonModifier::update(TgcGui::Message message)
{
	if(message.type == TgcGui::MessageType_Command && message.id == button->id)
	{
		pendingAction = true;
	}
}

void TgcButtonModifier::dispose()
{
}

bool TgcButtonModifier::consumeAction()
{
	if(pendingAction)
	{
		pendingAction = false;
		return true;
	}
	return false;
}

void TgcButtonModifier::setPosition(const Vector2 pos)
{
	button->position = pos;
}


