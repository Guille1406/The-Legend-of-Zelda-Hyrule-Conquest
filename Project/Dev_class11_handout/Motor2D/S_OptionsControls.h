#ifndef _S_OPTIONSCONTROLS_
#define _S_OPTIONSCONTROLS_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

class S_OptionsControls : public MainScene {

public:
	S_OptionsControls();
	~S_OptionsControls();
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
