#include <math.h>

#include "p2Log.h"
#include "j1HUD.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Player.h"
#include "j1GameStartMenuBack.h"
j1HUD::j1HUD()
{
	name ="hud";
}

j1HUD::~j1HUD()
{

}

// Called before render is available
bool j1HUD::Awake(pugi::xml_node& conf)
{
	LOG("Loading HUD atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	Life_Label =		{ 672,0,244,36 };
	Life_Label_x_pos = App->win->GetWindowWHalf() - Life_Label.w * 0.5f;
	Life_Label_y_pos = 11;
	Heart_Container =	{ 672,52,45,42 };
	Heart_Full =		{ 717,52,45,42 };
	Heart_Half =		{ 717,52,24,42 };
	Link_circle =       { 135,325,136,136 };
	Zelda_circle =		{ 0,325,136,136 };
	Sword =				{ 916,0,60,60 };
	Sword_centre =		{ (int)(Link_circle.w * 0.5f - Sword.w * 0.5f), (int)(Link_circle.h * 0.5f - Sword.h * 0.5f) };
	Bow =				{ 976,0,60,60 };
	Bow_centre =		{ (int)(Link_circle.w * 0.5f - Bow.w * 0.5f), (int)(Link_circle.h * 0.5f - Bow.h * 0.5f) };
	return ret;
}

// Called before the first frame
bool j1HUD::Start()
{
	atlas = App->tex->Load(atlas_file_name.c_str());
	return true;
}

// Called each loop iteration
bool j1HUD::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1HUD::Update(float dt)
{
	if (App->startmenuback->InGameMenuVisible())
		return true;

	//Blit Life Label
	App->render->Blit(atlas, -App->render->camera.x + Life_Label_x_pos, -App->render->camera.y + Life_Label_y_pos, &Life_Label, 1.0f, 0, INT_MAX, INT_MAX, false);
	
	//Calculate initial position
	int hearts_pos_x = App->win->GetWindowWHalf() - Heart_Container.w * App->player->hearts_containers_test_purpose * 0.5f - space_between_hearts * (App->player->hearts_containers_test_purpose * 0.5f - 0.5f);

	//Blit heart containers
	int heart_container_pos_x = hearts_pos_x;
	for (int heart = 0; heart < App->player->hearts_containers_test_purpose; heart++)
	{
		App->render->Blit(atlas, -App->render->camera.x + heart_container_pos_x, -App->render->camera.y + heart_container_pos_y, &Heart_Container, 1.0f, 0, INT_MAX, INT_MAX, false);
		heart_container_pos_x += (Heart_Container.w + space_between_hearts);
	}

	//Blit hearts (Life)
	int life_pos_x = hearts_pos_x;
	float full_hearts = App->player->half_hearts_test_purpose * 0.5f;
	for (int heart = 0; heart < (int)full_hearts; heart++)
	{
		App->render->Blit(atlas, -App->render->camera.x + life_pos_x, -App->render->camera.y + heart_container_pos_y, &Heart_Full, 1.0f, 0, INT_MAX, INT_MAX, false);
		life_pos_x += (Heart_Full.w + space_between_hearts);
	}
	float staff = 0.0f;
	float is_float = modf(full_hearts, &staff);
	if(is_float != 0.0f)
		App->render->Blit(atlas, -App->render->camera.x + life_pos_x, -App->render->camera.y + heart_container_pos_y, &Heart_Half, 1.0f, 0, INT_MAX, INT_MAX, false);

	//Blit Link circle
	App->render->Blit(atlas, -App->render->camera.x + item_circles_output, -App->render->camera.y + item_circles_output, &Link_circle, 1.0f, 0, INT_MAX, INT_MAX, false);

	//Blit Zelda circle
	App->render->Blit(atlas, -App->render->camera.x + App->win->GetWindowW() - Zelda_circle.w - item_circles_output, -App->render->camera.y + item_circles_output, &Zelda_circle, 1.0f, 0, INT_MAX, INT_MAX, false);

	//Blit Sword
	App->render->Blit(atlas, -App->render->camera.x + item_circles_output + Sword_centre.x, -App->render->camera.y + item_circles_output + Sword_centre.y, &Sword, 1.0f, 0, INT_MAX, INT_MAX, false);

	//Blit Bow
	App->render->Blit(atlas, -App->render->camera.x + App->win->GetWindowW() - Zelda_circle.w - item_circles_output + Bow_centre.x, -App->render->camera.y + item_circles_output + Bow_centre.x, &Bow, 1.0f, 0, INT_MAX, INT_MAX, false);

	//For some test
	/*
	if(App->input->GetKey(SDL_SCANCODE_1) == j1KeyState::KEY_DOWN)
	half_hearts_test_purpose += 1;
	if (App->input->GetKey(SDL_SCANCODE_2) == j1KeyState::KEY_DOWN)
	half_hearts_test_purpose -= 1;
	if (App->input->GetKey(SDL_SCANCODE_3) == j1KeyState::KEY_DOWN)
	half_hearts_test_purpose += 2;
	if (App->input->GetKey(SDL_SCANCODE_4) == j1KeyState::KEY_DOWN)
	half_hearts_test_purpose -= 2;
	if (App->input->GetKey(SDL_SCANCODE_5) == j1KeyState::KEY_DOWN)
	hearts_containers_test_purpose += 1;
	if (App->input->GetKey(SDL_SCANCODE_6) == j1KeyState::KEY_DOWN)
	hearts_containers_test_purpose -= 1;
	*/

	return true;
}

// Called each loop iteration
bool j1HUD::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1HUD::CleanUp()
{
	return true;
}

void j1HUD::OnGui(Gui* ui, GuiEvent event)
{

}

void j1HUD::OnConsoleCommand(const Command* command, const std::vector<std::string>& commandarguments)
{

}

void j1HUD::OnConsoleCVar(const CVar* cvar)
{

}

void j1HUD::ToggleVisibility(bool value)
{
	visible = value;
}