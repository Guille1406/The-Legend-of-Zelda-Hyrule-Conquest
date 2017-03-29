#include "j1App.h"
#include "j1Render.h"
#include "S_MainMenu.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Camera.h"
#include "Gui.h"
#include "GuiButton.h"
#include "j1GameStartMenuBack.h"

S_MainMenu::S_MainMenu()
{
}

S_MainMenu::~S_MainMenu()
{
}

bool S_MainMenu::Awake()
{
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	campaign = App->gui->CreateButton(iPoint(X_pos, 270), &std::string("Campaign"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	campaign->SetFont(App->font->Sherwood28);
	((Gui*)campaign)->SetListener(this);
	campaign->SetVisible(false);
	options = App->gui->CreateButton(iPoint(X_pos, 380), &std::string("Options"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	options->SetFont(App->font->Sherwood28);
	((Gui*)options)->SetListener(this);
	options->SetVisible(false);
	credits = App->gui->CreateButton(iPoint(X_pos, 490), &std::string("Credits"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	credits->SetFont(App->font->Sherwood28);
	((Gui*)credits)->SetListener(this);
	credits->SetVisible(false);
	quit = App->gui->CreateButton(iPoint(X_pos, 600), &std::string("Quit"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	quit->SetFont(App->font->Sherwood28);
	((Gui*)quit)->SetListener(this);
	quit->SetVisible(false);

	//For testing
	if (visibility)
	{
		campaign->SetVisible(true);
		options->SetVisible(true);
		credits->SetVisible(true);
		quit->SetVisible(true);
	}

	return true;
};

bool S_MainMenu::Start()
{
	App->player->Disable();
	App->camera->Disable();
	if (visibility)
	{
		campaign->SetVisible(true);
		options->SetVisible(true);
		credits->SetVisible(true);
		quit->SetVisible(true);
	}
	return true;
}

bool S_MainMenu::Update()
{
	//Blit title
	if (visibility)
	{
		int Title_X_pos = App->win->GetWindowWHalf() - (int)(title.w * 0.5f);
		App->render->Blit(App->gui->GetAtlas(), -App->render->camera.x + Title_X_pos, -App->render->camera.y + 40, &title, 1.0f, 0, INT_MAX, INT_MAX, false);
	}
	
	return true;
}

bool S_MainMenu::Clean()
{
	campaign->SetVisible(false);
	options->SetVisible(false);
	credits->SetVisible(false);
	quit->SetVisible(false);
	return true;
}

void S_MainMenu::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)campaign) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::world);
		App->startmenuback->Disable();
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