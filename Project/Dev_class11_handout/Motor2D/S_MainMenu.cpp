#include "j1App.h"
#include "j1Render.h"
#include "S_MainMenu.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Camera.h"
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
	int X_pos = App->win->GetWindowWHalf() - (int)(title_rec.w * 0.5f);
	title = App->gui->CreateImage(iPoint(X_pos, 40), &title_rec, false);
	((Gui*)title)->SetListener(this);
	title->SetVisible(false);
	X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	campaign = App->gui->CreateButton(iPoint(X_pos, 270), &std::string("Campaign"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	campaign->SetFont(App->font->Sherwood28);
	((Gui*)campaign)->SetListener(this);
	campaign->SetVisible(false);
	campaign->Focusable(true);
	options = App->gui->CreateButton(iPoint(X_pos, 380), &std::string("Options"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	options->SetFont(App->font->Sherwood28);
	((Gui*)options)->SetListener(this);
	options->SetVisible(false);
	options->Focusable(true);
	credits = App->gui->CreateButton(iPoint(X_pos, 490), &std::string("Credits"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	credits->SetFont(App->font->Sherwood28);
	((Gui*)credits)->SetListener(this);
	credits->SetVisible(false);
	credits->Focusable(true);
	quit = App->gui->CreateButton(iPoint(X_pos, 600), &std::string("Quit"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	quit->SetFont(App->font->Sherwood28);
	((Gui*)quit)->SetListener(this);
	quit->SetVisible(false);
	quit->Focusable(true);
	twitter = App->gui->CreateButton(iPoint(1039, 601), &std::string(""), ButtonType::idle_hover_pressed, &twitterrect_idle, &twitterrect_hover, &twitterrect_pressed, false);
	twitter->SetFont(App->font->Sherwood28);
	((Gui*)twitter)->SetListener(this);
	twitter->SetVisible(false);
	twitter->Focusable(true);
	github = App->gui->CreateButton(iPoint(1158, 601), &std::string(""), ButtonType::idle_hover_pressed, &githubrect_idle, &githubrect_hover, &githubrect_pressed, false);
	github->SetFont(App->font->Sherwood28);
	((Gui*)github)->SetListener(this);
	github->SetVisible(false);
	github->Focusable(true);

	buttons.push_back(campaign);
	buttons.push_back(options);
	buttons.push_back(credits);
	buttons.push_back(quit);
	buttons.push_back(twitter);
	buttons.push_back(github);

	return true;
};

bool S_MainMenu::Start()
{
	App->player->Disable();
	App->camera->Disable();
	App->enemy->Disable();
	App->object->Disable();

	if (visibility)
	{
		title->SetVisible(true);
		campaign->SetVisible(true);
		options->SetVisible(true);
		credits->SetVisible(true);
		quit->SetVisible(true);
		twitter->SetVisible(true);
		github->SetVisible(true);
	}

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_MainMenu::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->scene->ChangeScene(Scene_ID::world);
		App->startmenuback->Freeze(true);
	}
	
	MenuInput(&buttons);

	return true;
}

bool S_MainMenu::Clean()
{
	title->SetVisible(false);
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
		App->startmenuback->Freeze(true);
	}

	if ((ui == (Gui*)options) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::options);
	}

	if ((ui == (Gui*)credits) && (event == GuiEvent::mouse_lclk_down))
	{
		//App->scene->Show(Scene_ID::world);
	}

	if ((ui == (Gui*)quit) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::quitgame);
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