#ifndef __j1GAMESTARTBACKGROUND_H__
#define __j1GAMESTARTBACKGROUND_H__

#include "p2Point.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include "S_MainMenu.h"

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
	
private:
	SDL_Texture*	atlas = nullptr;
	std::string		atlas_file_name;

	SDL_Rect background = { 0,721,1278,1883 };
	int Background_Initial_pos = 0;
	int Background_pos = 0;
	int Background_speed = 2;
	j1Timer Background_timer;

};

#endif // __j1GAMESTARTBACKGROUND_H__