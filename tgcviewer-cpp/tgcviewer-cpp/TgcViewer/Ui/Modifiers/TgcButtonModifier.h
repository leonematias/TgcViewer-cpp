/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////



#pragma once


//General Includes:
#include <string>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Ui/Modifiers/TgcModifierItem.h"
#include "TgcViewer/Ui/Gui/TgcGuiButton.h"

//Forward declaration for "TgcViewer/GuiController.h"
namespace TgcViewer {class GuiController;}


namespace TgcViewer
{



/**
* A modifier with a Button that triggers a one-shot event
*/
class TgcButtonModifier : public TgcModifierItem
{

public:

	TgcButtonModifier(const string id, const string label);
	TgcButtonModifier(const TgcButtonModifier&);
	~TgcButtonModifier();


	//Virtual members
	virtual void update(TgcGui::Message message);
	virtual void dispose();
	virtual bool consumeAction();
	virtual void setPosition(const Vector2 pos);
	


private:
	
public:

	/**
	* Button widget
	*/
	TgcGuiButton* button;


	bool pendingAction;

private:

	
};




}