#ifndef _S_OPTIONSGAMEPLAY_
#define _S_OPTIONSGAMEPLAY_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_OptionsGameplay : public MainScene {

public:
	S_OptionsGameplay();
	~S_OptionsGameplay();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* GameplayLabel = nullptr;
	GuiButton* ShowhideHUD = nullptr;
	GuiCheck* ShowhideHUD_check = nullptr;
	GuiButton* Language = nullptr;
	GuiButton* back = nullptr;
	std::vector<GuiButton*> buttons;
};

#endif // #pragma once
