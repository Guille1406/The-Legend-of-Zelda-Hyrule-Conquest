#include "S_MainMenu.h"
#include "j1Player.h"
#include "j1Camera.h"
#include "Gui.h"
#include "GuiButton.h"

S_MainMenu::S_MainMenu()
{
}

S_MainMenu::~S_MainMenu()
{
}

bool S_MainMenu::Start()
{
	App->player->Disable();
	App->camera->Disable();
	SDL_Rect idle_button_rect = { 410,165,231,73 };
	SDL_Rect hover_button_rect = { -1,109,231,73 };
	SDL_Rect pressed_button_rect = { 641,165,231,73 };
	campain = App->gui->CreateButton(iPoint(1000, 370), &std::string("Campain"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	campain->SetFont(App->font->Sherwood20);
	((Gui*)campain)->SetListener(this);
	options = App->gui->CreateButton(iPoint(1000, 450), &std::string("Options"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	options->SetFont(App->font->Sherwood20);
	((Gui*)options)->SetListener(this);
	credits = App->gui->CreateButton(iPoint(1000, 530), &std::string("Credits"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	credits->SetFont(App->font->Sherwood20);
	((Gui*)credits)->SetListener(this);
	quit = App->gui->CreateButton(iPoint(1000, 610), &std::string("Quit"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	quit->SetFont(App->font->Sherwood20);
	((Gui*)quit)->SetListener(this);
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
	if ((ui == (Gui*)campain) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::world);
	}

	if ((ui == (Gui*)options) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}

	if ((ui == (Gui*)credits) && (event == GuiEvent::mouse_lclk_down))
	{
		//App->scene->ChangeScene(Scene_ID::world);
	}

	if ((ui == (Gui*)quit) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::quitgame);
	}
}