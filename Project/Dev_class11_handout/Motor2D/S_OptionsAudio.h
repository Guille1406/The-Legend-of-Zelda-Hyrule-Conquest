#ifndef _S_OPTIONSAUDIO_
#define _S_OPTIONSAUDIO_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_OptionsAudio : public MainScene {

public:
	S_OptionsAudio();
	~S_OptionsAudio();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* AudioLabel = nullptr;
	GuiButton* MasterVolume = nullptr;
	//GuiButton* MusicVolume = nullptr;
	//GuiButton* SFXVolume = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once
