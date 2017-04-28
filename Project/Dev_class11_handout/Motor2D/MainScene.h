#ifndef _MAINSCENE_
#define _MAINSCENE_

#include <vector>

#include "j1App.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "p2Log.h"
#include "j1DialogueManager.h"

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
	tempbossroom,
	colourpuzzle,
	dungeon,
	Send,
	testenemies,

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
	virtual bool Load(pugi::xml_node&){
		return true;
	}
	virtual bool Save(pugi::xml_node&) const{
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

	void MenuInput(std::vector<GuiButton*>* buttons);

public:
	std::string scene_str = empty_char;
	Scene_ID scene_name;
	
	SDL_Rect background = { 1278,1414,593,94 };
	SDL_Rect label_title_rec = { 1278,1832,593,94 };

	SDL_Rect idle_button_rect = { 0,320,348,106 };
	SDL_Rect hover_button_rect = { 0,212,348,106 };
	SDL_Rect pressed_button_rect = { 0,428,348,106 };

	SDL_Rect idle_check_rect = { 349,211,48,48 };
	SDL_Rect pressed_check_rect = { 349,259,48,48 };

	std::vector<GuiButton*> buttons;

};

#endif // !_MAINSCENE_