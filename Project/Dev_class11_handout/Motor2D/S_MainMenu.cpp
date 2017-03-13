#include "S_MainMenu.h"
#include"j1Player.h"
S_MainMenu::S_MainMenu()
{
}

S_MainMenu::~S_MainMenu()
{
}

bool S_MainMenu::Start()
{
	App->player->Disable();
	SDL_Rect idle_button_rect = { 410,165,231,73 };
	SDL_Rect hover_button_rect = { -1,109,231,73 };
	SDL_Rect pressed_button_rect = { 641,165,231,73 };
	idle_hoover_pressed_button = App->gui->CreateButton(iPoint(700, 400), &std::string("Idle/Hover/Pressed Button"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	
	return true;
}

bool S_MainMenu::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		App->scene->ChangeScene(world);
		
		
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		App->scene->ChangeScene(dungeon);
	}
	return true;
}

bool S_MainMenu::Clean()
{
	return true;
}
