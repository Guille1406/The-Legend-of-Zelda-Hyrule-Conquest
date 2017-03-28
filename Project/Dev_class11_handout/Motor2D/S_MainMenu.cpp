#include "j1App.h"
#include "j1Render.h"
#include "S_MainMenu.h"
#include "j1Player.h"
#include "j1Window.h"
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
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	campain = App->gui->CreateButton(iPoint(X_pos, 270), &std::string("Campain"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	campain->SetFont(App->font->Sherwood28);
	((Gui*)campain)->SetListener(this);
	campain->SetVisible(false);
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

	Background_Initial_pos = App->win->GetWindowH() - background.h;

	//For testing
	if (visibility)
	{
		campain->SetVisible(true);
		options->SetVisible(true);
		credits->SetVisible(true);
		quit->SetVisible(true);
	}

	Background_timer.Start();

	return true;
}

bool S_MainMenu::Update()
{
	//Blit background
	int Background_Y_Pos = -App->render->camera.y + Background_Initial_pos + Background_pos;
	App->render->Blit(App->gui->GetAtlas(), -App->render->camera.x, Background_Y_Pos, &background, 1.0f, 0, INT_MAX, INT_MAX, false);
	//Blit background
	if (Background_Y_Pos < -1)
	{
		if (Background_timer.Read() > Background_speed)
		{
			Background_pos += 2;
			Background_timer.Start();
		}
	}
	else
		if (!visibility)
		{
			campain->SetVisible(true);
			options->SetVisible(true);
			credits->SetVisible(true);
			quit->SetVisible(true);
			visibility = true;
		}

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