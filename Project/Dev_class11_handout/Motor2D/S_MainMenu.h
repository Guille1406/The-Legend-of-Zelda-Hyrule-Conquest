#ifndef _S_MAIN_MENU_
#define _S_MAIN_MENU_

#include <vector>

#include "j1App.h"
#include "j1Scene.h"
#include "MainScene.h"
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
	SDL_Rect title =				{ 0,0,493,211 };
	SDL_Rect twitterrect_idle =		{ 1278,1508,108,108 };
	SDL_Rect twitterrect_hover =	{ 1278,1616,108,108 };
	SDL_Rect twitterrect_pressed =	{ 1278,1724,108,108 };
	SDL_Rect githubrect_idle =		{ 1386,1508,108,108 };
	SDL_Rect githubrect_hover =		{ 1386,1616,108,108 };
	SDL_Rect githubrect_pressed =   { 1386,1724,108,108 };
	GuiButton* campaign =	 nullptr;
	GuiButton* options =	 nullptr;
	GuiButton* credits =	 nullptr;
	GuiButton* quit =	   	 nullptr;
	GuiButton* twitter =	 nullptr;
	GuiButton* github =		 nullptr;
	std::vector<GuiButton*> buttons;
	bool visibility =		 false;
	uint titleopacity =		 0;
};

#endif // #pragma once
