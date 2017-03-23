#include "S_MainMenu.h"
#include"j1Player.h"
#include "Gui.h"
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
	idle_hoover_pressed_button = App->gui->CreateButton(iPoint(700, 400), &std::string("Go to awesome adventure :)"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)idle_hoover_pressed_button)->SetListener(this);

	return true;
}

bool S_MainMenu::Update()
{
	return true;
}

bool S_MainMenu::Clean()
{
	return true;
}

void S_MainMenu::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)idle_hoover_pressed_button) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(world);
	}
}