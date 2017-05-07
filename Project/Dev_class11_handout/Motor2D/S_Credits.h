#ifndef _S_CREDITS_
#define _S_CREDITS_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_Credits : public MainScene {

public:
	S_Credits();
	~S_Credits();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
public:
	/*
	GuiButton* AudioLabel = nullptr;
	GuiButton* MasterVolume = nullptr;
	//GuiButton* MusicVolume = nullptr;
	//GuiButton* SFXVolume = nullptr;
	*/
	GuiButton* back = nullptr;
};

#endif // #pragma once
