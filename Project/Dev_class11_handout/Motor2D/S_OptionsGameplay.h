#ifndef _S_OPTIONSGAMEPLAY_
#define _S_OPTIONSGAMEPLAY_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

class S_OptionsGameplay : public MainScene {

public:
	S_OptionsGameplay();
	~S_OptionsGameplay();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiLabel* OptionsLabel = nullptr;
	GuiButton* controls = nullptr;
	GuiButton* video = nullptr;
	GuiButton* audio = nullptr;
	GuiButton* gameplay = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once
