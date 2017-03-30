#ifndef __j1HUD_H__
#define __j1HUD_H__

#include "p2Point.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"

class j1HUD : public j1Module
{
public:
	j1HUD();

	~j1HUD();

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

	void OnGui(Gui* ui, GuiEvent event);

	void OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments);

	void OnConsoleCVar(const CVar* cvar);

	void ToggleVisibility(bool value);

	
private:
	bool visible = true;

	SDL_Texture*	atlas = nullptr;
	std::string		atlas_file_name;

	SDL_Rect Life_Label;
	SDL_Rect Heart_Container;
	SDL_Rect Heart_Full;
	SDL_Rect Heart_Half;
	SDL_Rect Link_circle;
	SDL_Rect Zelda_circle;
	//Items
	SDL_Rect Sword;
	SDL_Rect Bow;

	//Drawing variables
	uint Life_Label_x_pos = 0;
	uint Life_Label_y_pos = 0;
	uint space_between_hearts = 4;
	uint heart_container_pos_y = 60;
	uint item_circles_output = 20;
	//Items centre from upper left corner of circle
	iPoint Sword_centre = { 0,0 };
	iPoint Bow_centre = { 0,0 };

	

};

#endif // __j1HUD_H__