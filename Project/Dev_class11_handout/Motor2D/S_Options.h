#ifndef _S_OPTIONS_
#define _S_OPTIONS_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"

class S_Options : public MainScene {

public:
	S_Options();
	~S_Options();
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
