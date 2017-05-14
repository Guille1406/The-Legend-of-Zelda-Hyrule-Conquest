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
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* newcampaign = nullptr;
	GuiButton* loadcampaign = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once