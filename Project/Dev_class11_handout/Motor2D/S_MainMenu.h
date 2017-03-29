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
	SDL_Texture*	atlas = nullptr;
	std::string		atlas_file_name;
	SDL_Rect title =		 { 0,0,493,211 };
	SDL_Rect LinkRect =		 { 1058,0,819,720 };
	SDL_Rect ZeldaRect =	 { 493,0,565,720 };
	SDL_Rect MessengerRect = { 1078,720,599,694 };
	GuiButton* campaign =	nullptr;
	GuiButton* options =	nullptr;
	GuiButton* credits =	nullptr;
	GuiButton* quit =		nullptr;
	bool visibility =		true;
	uint titleopacity = 0;
};

#endif // #pragma once
