#ifndef _S_MAIN_MENU_
#define _S_MAIN_MENU_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"
#include "j1Timer.h"

class S_MainMenu : public MainScene {

public:
	S_MainMenu();
	~S_MainMenu();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
private:
	SDL_Rect title =		{ 0,0,493,211 };
	SDL_Rect background =	{ 0,721,1278,1883 };
	GuiButton* campain =	nullptr;
	GuiButton* options =	nullptr;
	GuiButton* credits =	nullptr;
	GuiButton* quit =		nullptr;
	bool visibility =		true;
	int Background_Initial_pos = 0;
	int Background_pos = 0;
	int Background_speed = 2;
	j1Timer Background_timer;
};

#endif // #pragma once
