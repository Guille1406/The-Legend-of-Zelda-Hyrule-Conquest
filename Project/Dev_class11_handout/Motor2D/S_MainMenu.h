#ifndef _S_MAIN_MENU_
#define _S_MAIN_MENU_

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Gui.h"
#include "j1Timer.h"

class S_MainMenu : public MainScene
{
	friend j1GameStartMenuBackground;
public:
	S_MainMenu();
	~S_MainMenu();
	bool Awake();
	bool Start();
	bool Update();
	bool Clean();
	void OnGui(Gui* ui, GuiEvent event);
private:
	SDL_Rect title =		 { 0,0,493,211 };
	GuiButton* campaign =	 nullptr;
	GuiButton* options =	 nullptr;
	GuiButton* credits =	 nullptr;
	GuiButton* quit =	   	 nullptr;
	bool visibility =		 false;
	uint titleopacity =		 0;
};

#endif // #pragma once
