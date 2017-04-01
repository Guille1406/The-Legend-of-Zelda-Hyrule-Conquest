#ifndef __j1GAMESTARTBACKGROUND_H__
#define __j1GAMESTARTBACKGROUND_H__

#include <list>

#include "p2Point.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include "S_MainMenu.h"

struct BackgroundCharacter
{
	BackgroundCharacter(SDL_Rect* sdlrect, iPoint point): rect(*sdlrect), position(point)
	{

	}

	~BackgroundCharacter()
	{

	}

	SDL_Rect rect;
	iPoint position = { 0,0 };
};

class j1GameStartMenuBackground : public j1Module
{
public:
	j1GameStartMenuBackground();

	~j1GameStartMenuBackground();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
	
	void Freeze(bool freeze);

private:
	bool ingamenushow = false;

	SDL_Texture* atlas =		nullptr;
	std::string	atlas_file_name;

	SDL_Rect background =		{ 0,721,1278,1883 };
	std::list<BackgroundCharacter*> BackgroundCharacterList;
	SDL_Rect LinkRect =			{ 1058,0,819,720 };
	SDL_Rect ZeldaRect =		{ 493,0,565,720 };
	SDL_Rect MessengerRect =	{ 1278,720,599,694 };
	int Background_Initial_pos = 0;
	int Background_pos =		0; 
	int Background_speed =		2;
	j1Timer Background_timer;
	j1Timer MainMenuOpacity_timer;
	uint startmenuopacity =		0;
	bool activate_background_movement = false;
	bool background_movement =  false;
	j1Timer Background_Characters_timer;
	int backgroundcharactersspeed = 10;
	int spacebetweenbackgroundcharacters = 500;
	bool firstloop = false;
	bool freeze = false;
};

#endif // __j1GAMESTARTBACKGROUND_H__