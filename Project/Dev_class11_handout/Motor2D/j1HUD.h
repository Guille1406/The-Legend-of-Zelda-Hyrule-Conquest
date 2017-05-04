#ifndef __j1HUD_H__
#define __j1HUD_H__

#include "p2Point.h"
#include "j1Module.h"
#include "j1Timer.h"
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

	SDL_Texture* GetAtlas();

	void SceneChanged()
	{
		scene_changed = true;
	}

private:
	bool visible = true;

	SDL_Texture*	atlas = nullptr;
	std::string		atlas_file_name = empty_char;

	SDL_Rect Life_Label = { 672,0,244,36 };
	SDL_Rect Heart_Container = { 672,52,45,42 };
	SDL_Rect Heart_Full = { 717,52,45,42 };
	SDL_Rect Heart_Half = { 717,52,24,42 };
	SDL_Rect Link_circle = { 135,325,136,136 };
	SDL_Rect Zelda_circle = { 0,325,136,136 };
	SDL_Rect Link_circle_L = { 342,325,70,55 };
	SDL_Rect Zelda_circle_R = { 272,325,70,55 };
	//Items
	SDL_Rect Sword = { 916,0,60,60 };
	SDL_Rect Bow = { 976,4,56,56 };

	SDL_Rect PlaceLabelBack = { 564,325,498,137 };

	//Drawing variables
	uint Life_Label_x_pos = 0;
	uint Life_Label_y_pos = 0;
	uint space_between_hearts = 4;
	uint heart_container_pos_y = 60;
	uint item_circles_output = 20;
	//Items centre from upper left corner of circle
	iPoint Sword_centre = { 0,0 };
	iPoint Bow_centre = { 0,0 };
	uint LRbuttonsoffset = 10;
	
	j1Timer PlaceLabel_timer;
	SDL_Texture* texture_label_to_blit = nullptr;
	int texture_label_to_blit_w, texture_label_to_blit_h = 0;
	bool scene_changed = false;
	int PlaceLabel_opacity = 255;

};

#endif // __j1HUD_H__