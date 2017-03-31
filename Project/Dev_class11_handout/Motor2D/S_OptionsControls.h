#ifndef _S_OPTIONSCONTROLS_
#define _S_OPTIONSCONTROLS_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

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
	GuiButton* ControllerSensibility = nullptr;
	GuiButton* MouseSensibility = nullptr;
	GuiButton* ControllerLayout = nullptr;
	GuiButton* MouseLayout = nullptr;
	GuiButton* back = nullptr;
	std::vector<GuiButton*> buttons;
};

#endif // #pragma once
