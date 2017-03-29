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
	bool Awake();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiLabel* ControlsLabel = nullptr;
	GuiLabel* ControllerSensibility = nullptr;
	GuiLabel* MouseSensibility = nullptr;
	GuiButton* ControllerLayout = nullptr;
	GuiButton* MouseLayout = nullptr;
	GuiButton* back = nullptr;
};

#endif // #pragma once
