#ifndef _S_CAMPAIGN_
#define _S_CAMPAIGN_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

class S_Campaign : public MainScene {

public:
	S_Campaign();
	~S_Campaign();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiImage* controllerlayout = nullptr;
	GuiButton* newcampaign = nullptr;
	GuiButton* back = nullptr;
	std::vector<GuiButton*> buttons;

	SDL_Rect controllerlayout_rec = { 0,2604,1278,720 };
};

#endif // #pragma once