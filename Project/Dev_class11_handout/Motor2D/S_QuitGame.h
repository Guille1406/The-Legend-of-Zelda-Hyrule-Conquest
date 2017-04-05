#ifndef _S_QUITGAME_
#define _S_QUITGAME_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"

class S_QuitGame : public MainScene {

public:
	S_QuitGame();
	~S_QuitGame();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
public:
	GuiButton* Label =		nullptr;
	GuiButton* Yes =		nullptr;
	GuiButton* No =			nullptr;
};

#endif // #pragma once
