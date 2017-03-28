#ifndef __j1HUD_H__
#define __j1HUD_H__

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

	//Drawing variables
	uint half_window_w = 0;
	uint Life_Label_x_pos = 0;
	uint Life_Label_y_pos = 0;
	uint space_between_hearts = 4;
	uint heart_container_pos_y = 60;

	//--------------------------------------------------------------------------------------//
	//--------------------------------This must be in player--------------------------------//
	//--------------------------------------------------------------------------------------//
	uint hearts_containers_test_purpose = 4;	//Total half hearts that the player have, how many FULL hearts containers have
	uint half_hearts_test_purpose = 8;		//Current half hearts life
	//Example
	// half_hearts_test_purpose = 6, means that you have 3 heart containers
	// half_hearts_life_test_purpose = 3, means that you have 1,5 hearts out of 3 full ones

};

#endif // __j1HUD_H__