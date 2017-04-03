#ifndef _MAINSCENE_
#define _MAINSCENE_

#include <vector>

#include "j1App.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "p2Log.h"

#include "j1Gui.h"
#include "GuiImage.h"
#include "GuiLabel.h"
#include "GuiButton.h"
#include "GuiCheck.h"

enum Scene_ID {
	//Main menu
	mainmenu,
	campaign,
	options,
	optionsaudio,
	optionscontrols,
	optionsvideo,
	optionsgameplay,
	credits,
	quitgame,
	//ingame menu
	ingamemenu,

	//Maps
	map,
	world,
	dungeon,
	Send, 

};

enum GuiEvent;
class Gui;
struct Command;
struct CVar;
class GuiButton;

class MainScene {
public:

	MainScene() {};
	~MainScene() {};

	virtual bool Awake(pugi::xml_node& conf) {
		return true;
	};

	virtual bool Start() {
		return true;
	};
	
	virtual bool PreUpdate() {
		return true;
	};
	virtual bool Update() {
		return true;
	};
	virtual bool PostUpdate() {
		return true;
	};
	virtual bool Clean() {
		return true;
	}
	virtual void OnGui(Gui* ui, GuiEvent event)
	{
	}
	virtual void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
	{
	}
	virtual void OnConsoleCVar(const CVar* cvar)
	{
	}

protected:

	void MenuInput(std::vector<GuiButton*>* buttons)
	{
		if ((App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) || (App->input->GetControllerButton(0, 11) == KEY_DOWN))
		{
			std::vector<GuiButton*>::iterator focused_button = std::find(buttons->begin(), buttons->end(), App->gui->GetFocus());
			if ((*focused_button) != buttons->front())
			{
				focused_button--;
				App->gui->SetFocus((*(focused_button)));
			}
		}

		if ((App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) || (App->input->GetControllerButton(0, 12) == KEY_DOWN))
		{
			std::vector<GuiButton*>::iterator focused_button = std::find(buttons->begin(), buttons->end(), App->gui->GetFocus());
			if ((*focused_button) != buttons->back())
			{
				focused_button++;
				App->gui->SetFocus((*(focused_button)));
			}
		}
	}

public:
	std::string scene_str = empty_char;
	Scene_ID scene_name;
	
	
	/*
	Map
	Textures
	Enemies
	.
	.
	.
	*/

	SDL_Rect idle_button_rect = { 0,320,348,106 };
	SDL_Rect hover_button_rect = { 0,212,348,106 };
	SDL_Rect pressed_button_rect = { 0,428,348,106 };

	SDL_Rect idle_check_rect = { 349,211,48,48 };
	SDL_Rect pressed_check_rect = { 349,259,48,48 };

};

#endif // !_MAINSCENE_