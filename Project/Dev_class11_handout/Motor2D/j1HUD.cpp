#include "p2Log.h"
#include "j1HUD.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Input.h"

j1HUD::j1HUD()
{
	name.create("hud");
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
	//For some test
	if(App->input->GetKey(SDL_SCANCODE_1) == j1KeyState::KEY_DOWN)
		half_hearts_test_purpose += 1;
	if (App->input->GetKey(SDL_SCANCODE_2) == j1KeyState::KEY_DOWN)
		half_hearts_test_purpose -= 1;
	if (App->input->GetKey(SDL_SCANCODE_3) == j1KeyState::KEY_DOWN)
		half_hearts_test_purpose += 2;
	if (App->input->GetKey(SDL_SCANCODE_4) == j1KeyState::KEY_DOWN)
		half_hearts_test_purpose -= 2;



	
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