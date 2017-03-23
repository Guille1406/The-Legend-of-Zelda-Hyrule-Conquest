#ifndef _S_CAMPAIN_
#define _S_CAMPAIN_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

class S_Campain : public MainScene {

public:
	S_Campain();
	~S_Campain();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* campain = nullptr;
	GuiButton* options = nullptr;
	GuiButton* credits = nullptr;
	GuiButton* quit = nullptr;
};

#endif // #pragma once
