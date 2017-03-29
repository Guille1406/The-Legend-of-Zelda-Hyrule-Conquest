#ifndef _S_OPTIONSAUDIO_
#define _S_OPTIONSAUDIO_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

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
	GuiLabel* MasterVolume = nullptr;
	GuiLabel* MusicVolume = nullptr;
	GuiLabel* SFXVolume = nullptr;
	GuiScrollBar* MasterVolumeScrollBar = nullptr;
	GuiScrollBar* MusicVolumeScrollBar = nullptr;
	GuiScrollBar* SFXVolumeScrollBar = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once
