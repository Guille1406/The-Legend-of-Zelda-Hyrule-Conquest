#include "j1App.h"
#include "j1Render.h"
#include "S_InGameMenu.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Camera.h"
#include "j1HUD.h"
#include "j1Pathfinding.h"
#include "Gui.h"
#include "GuiButton.h"
#include "j1GameStartMenuBack.h"
#include "j1Audio.h"

S_InGameMenu::S_InGameMenu()
{
	scene_str = "InGameMenu";
}

S_InGameMenu::~S_InGameMenu()
{
}

bool S_InGameMenu::Awake(pugi::xml_node& conf)
{
	IngamemenuLabel = App->gui->CreateButton(iPoint(40,40), &std::string(conf.child("IngamemenuLabel").attribute("value").as_string("In-Game menu")), ButtonType::idle_only, &label_title_rec, false);
	IngamemenuLabel->SetFont(App->font->Triforce48);
	((Gui*)IngamemenuLabel)->SetListener(this);
	IngamemenuLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	resume = App->gui->CreateButton(iPoint(X_pos, 160), &std::string(conf.child("resume").attribute("value").as_string("Resume")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	resume->SetFont(App->font->Sherwood20);
	((Gui*)resume)->SetListener(this);
	resume->SetVisible(false);
	resume->Focusable(true);
	loadcheckpoint = App->gui->CreateButton(iPoint(X_pos, 270), &std::string(conf.child("loadcheckpoint").attribute("value").as_string("Load Last Checkpoint")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	loadcheckpoint->SetFont(App->font->Sherwood20);
	((Gui*)loadcheckpoint)->SetListener(this);
	loadcheckpoint->SetVisible(false);
	loadcheckpoint->Focusable(true);
	options = App->gui->CreateButton(iPoint(X_pos, 380), &std::string(conf.child("options").attribute("value").as_string("Options")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	options->SetFont(App->font->Sherwood20);
	((Gui*)options)->SetListener(this);
	options->SetVisible(false);
	options->Focusable(true);
	mainmenu = App->gui->CreateButton(iPoint(X_pos, 490), &std::string(conf.child("mainmenu").attribute("value").as_string("Main Menu")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	mainmenu->SetFont(App->font->Sherwood20);
	((Gui*)mainmenu)->SetListener(this);
	mainmenu->SetVisible(false);
	mainmenu->Focusable(true);
	quit = App->gui->CreateButton(iPoint(X_pos, 600), &std::string(conf.child("quit").attribute("value").as_string("Quit")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	quit->SetFont(App->font->Sherwood20);
	((Gui*)quit)->SetListener(this);
	quit->SetVisible(false);
	quit->Focusable(true);

	buttons.push_back(resume);
	buttons.push_back(loadcheckpoint);
	buttons.push_back(options);
	buttons.push_back(mainmenu);
	buttons.push_back(quit);
	return true;
};

bool S_InGameMenu::Start()
{
	IngamemenuLabel->SetVisible(true);
	resume->SetVisible(true);
	loadcheckpoint->SetVisible(true);
	options->SetVisible(true);
	mainmenu->SetVisible(true);
	quit->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	active = true;

	return true;
}

bool S_InGameMenu::Update()
{
	/*
	//Blit title
	if (visibility)
	{
		int Title_X_pos = App->win->GetWindowWHalf() - (int)(title.w * 0.5f);
		App->render->Blit(App->gui->GetAtlas(), -App->render->camera.x + Title_X_pos, -App->render->camera.y + 40, &title, 1.0f, 0, INT_MAX, INT_MAX, false, titleopacity);
	}
	*/
	MenuInput(&buttons);
	return true;
}

bool S_InGameMenu::Clean()
{
	IngamemenuLabel->SetVisible(false);
	resume->SetVisible(false);
	loadcheckpoint->SetVisible(false);
	options->SetVisible(false);
	mainmenu->SetVisible(false);
	quit->SetVisible(false);
	App->gui->SetFocus(nullptr);

	active = false;

	return true;
}

void S_InGameMenu::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)resume) && (event == GuiEvent::mouse_lclk_down))
	{
		App->player->paused = !App->player->paused;
		App->enemy->paused = !App->enemy->paused;
		App->collision->paused = !App->collision->paused;
		App->pathfinding->paused = !App->pathfinding->paused;
		App->scene->Hide();
		App->startmenuback->Freeze(true);
	}
	if ((ui == (Gui*)loadcheckpoint) && (event == GuiEvent::mouse_lclk_down))
	{
		//By now this do nothing
	}
	if ((ui == (Gui*)options) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::options);
	}
	if ((ui == (Gui*)mainmenu) && (event == GuiEvent::mouse_lclk_down))
	{
		App->audio->VolumeMusic(0);
		App->player->Disable();
		App->enemy->Disable();
		App->map->Disable();
		App->collision->Disable();
		App->hud->Disable();
		App->object->Disable();
		App->scene->ChangeScene(Scene_ID::mainmenu);
		App->scene->Hide();
		active = false;
	}
	if ((ui == (Gui*)quit) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::quitgame);
	}
}