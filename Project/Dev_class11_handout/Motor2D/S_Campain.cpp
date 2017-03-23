#include "S_Campain.h"
#include "j1Player.h"
#include "Gui.h"

S_Campain::S_Campain()
{
}

S_Campain::~S_Campain()
{
}

bool S_Campain::Start()
{
	/*
	App->player->Disable();
	SDL_Rect idle_button_rect = { 410,165,231,73 };
	SDL_Rect hover_button_rect = { -1,109,231,73 };
	SDL_Rect pressed_button_rect = { 641,165,231,73 };
	campain = App->gui->CreateButton(iPoint(1000, 370), &std::string("Campain"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)campain)->SetListener(this);
	options = App->gui->CreateButton(iPoint(1000, 450), &std::string("Options"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)options)->SetListener(this);
	credits = App->gui->CreateButton(iPoint(1000, 530), &std::string("Credits"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)credits)->SetListener(this);
	quit = App->gui->CreateButton(iPoint(1000, 610), &std::string("Quit"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)quit)->SetListener(this);
	*/
	return true;
}

bool S_Campain::Update()
{
	return true;
}

bool S_Campain::Clean()
{
	return true;
}

void S_Campain::OnGui(Gui* ui, GuiEvent event)
{
	/*
	if ((ui == (Gui*)campain) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(world);
	}

	if ((ui == (Gui*)options) && (event == GuiEvent::mouse_lclk_down))
	{
		//App->scene->ChangeScene(world);
	}

	if ((ui == (Gui*)credits) && (event == GuiEvent::mouse_lclk_down))
	{
		//App->scene->ChangeScene(world);
	}

	if ((ui == (Gui*)quit) && (event == GuiEvent::mouse_lclk_down))
	{
		//App->scene->ChangeScene(world);
	}
	*/
}