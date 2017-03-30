#ifndef _S_GAME_START_
#define _S_GAME_START_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_GameStart : public MainScene {

public:
	S_GameStart();
	~S_GameStart();
	bool Awake();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* campaign = nullptr;
	GuiButton* options = nullptr;
	GuiButton* credits = nullptr;
	GuiButton* quit = nullptr;
};

#endif // #pragma once
