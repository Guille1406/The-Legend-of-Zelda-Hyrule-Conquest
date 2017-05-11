#ifndef _S_DEATH_
#define _S_DEATH_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_Death : public MainScene {

public:
	S_Death();
	~S_Death();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
public:
	SDL_Rect CreditsLogo_Rect = { 0,0,0,0 };
	SDL_Rect CreditsBack_Rect = { 0,0,0,0 };
	SDL_Rect CreditsBackHover_Rect = { 0,0,0,0 };
	GuiImage* CreditsLogo = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once
