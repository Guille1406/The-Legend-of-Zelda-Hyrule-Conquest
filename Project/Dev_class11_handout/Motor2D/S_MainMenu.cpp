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
	//visibility = true;
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
	twitter = App->gui->CreateButton(iPoint(1039, 601), &std::string(""), ButtonType::idle_only, &twitterrect, false);
	twitter->SetFont(App->font->Sherwood28);
	((Gui*)twitter)->SetListener(this);
	twitter->SetVisible(false);
	github = App->gui->CreateButton(iPoint(1158, 601), &std::string(""), ButtonType::idle_only, &githubrect, false);
	github->SetFont(App->font->Sherwood28);
	((Gui*)github)->SetListener(this);
	github->SetVisible(false);
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
		twitter->SetVisible(true);
		github->SetVisible(true);
	}

	return true;
}

bool S_MainMenu::Update()
{
	//Blit title
	if (visibility)
	{
		int Title_X_pos = App->win->GetWindowWHalf() - (int)(title.w * 0.5f);
		App->render->Blit(App->gui->GetAtlas(), -App->render->camera.x + Title_X_pos, -App->render->camera.y + 40, &title, 1.0f, 0, INT_MAX, INT_MAX, false, titleopacity);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		App->scene->ChangeScene(Scene_ID::world);
		App->startmenuback->Disable();
	}
	
	return true;
}

bool S_MainMenu::Clean()
{
	campaign->SetVisible(false);
	options->SetVisible(false);
	credits->SetVisible(false);
	quit->SetVisible(false);
	twitter->SetVisible(false);
	github->SetVisible(false);
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

	if ((ui == (Gui*)twitter) && (event == GuiEvent::mouse_lclk_down))
	{
		ShellExecute(NULL, "open", "https://twitter.com/Summit_Games?lang=en", NULL, NULL, SW_SHOWMAXIMIZED);
	}

	if ((ui == (Gui*)github) && (event == GuiEvent::mouse_lclk_down))
	{
		ShellExecute(NULL, "open", "https://github.com/Guille1406/The-Legend-of-Zelda-Hyrule-Conquest", NULL, NULL, SW_SHOWMAXIMIZED);
	}
}