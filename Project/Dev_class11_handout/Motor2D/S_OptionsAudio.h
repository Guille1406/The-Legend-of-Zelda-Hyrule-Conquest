#ifndef _S_OPTIONSAUDIO_
#define _S_OPTIONSAUDIO_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_OptionsAudio : public MainScene {

public:
	S_OptionsAudio();
	~S_OptionsAudio();
	bool Awake();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiLabel* AudioLabel = nullptr;
	GuiButton* MasterVolume = nullptr;
	GuiButton* MusicVolume = nullptr;
	GuiButton* SFXVolume = nullptr;
	GuiButton* back = nullptr;
	std::vector<GuiButton*> buttons;
};

#endif // #pragma once
