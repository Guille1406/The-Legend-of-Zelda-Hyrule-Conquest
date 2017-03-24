#ifndef _S_OPTIONSVIDEO_
#define _S_OPTIONSVIDEO_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

class S_OptionsVideo : public MainScene {

public:
	S_OptionsVideo();
	~S_OptionsVideo();
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
