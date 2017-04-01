#include "j1App.h"
#include "j1Render.h"
#include "S_InGameMenu.h"
#include "j1Player.h"
#include "j1Window.h"
#include "j1Camera.h"
#include "Gui.h"
#include "GuiButton.h"
#include "j1GameStartMenuBack.h"

S_InGameMenu::S_InGameMenu()
{
}

S_InGameMenu::~S_InGameMenu()
{
}

bool S_InGameMenu::Awake()
{
	IngamemenuLabel = App->gui->CreateLabel(iPoint(200, 100), &std::string("In-Game menu"), false);
	IngamemenuLabel->SetFont(App->font->Sherwood28);
	((Gui*)IngamemenuLabel)->SetListener(this);
	IngamemenuLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	resume = App->gui->CreateButton(iPoint(X_pos, 160), &std::string("Resume"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	resume->SetFont(App->font->Sherwood20);
	((Gui*)resume)->SetListener(this);
	resume->SetVisible(false);
	resume->Focusable(true);
	loadcheckpoint = App->gui->CreateButton(iPoint(X_pos, 270), &std::string("Load Last Checkpoint"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	loadcheckpoint->SetFont(App->font->Sherwood20);
	((Gui*)loadcheckpoint)->SetListener(this);
	loadcheckpoint->SetVisible(false);
	loadcheckpoint->Focusable(true);
	options = App->gui->CreateButton(iPoint(X_pos, 380), &std::string("Options"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	options->SetFont(App->font->Sherwood20);
	((Gui*)options)->SetListener(this);
	options->SetVisible(false);
	options->Focusable(true);
	mainmenu = App->gui->CreateButton(iPoint(X_pos, 490), &std::string("Main Menu"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	mainmenu->SetFont(App->font->Sherwood20);
	((Gui*)mainmenu)->SetListener(this);
	mainmenu->SetVisible(false);
	mainmenu->Focusable(true);
	quit = App->gui->CreateButton(iPoint(X_pos, 600), &std::string("Quit"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
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
	return true;
}

void S_InGameMenu::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)resume) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Hide();
		App->startmenuback->Freeze(true);
	}
	if ((ui == (Gui*)loadcheckpoint) && (event == GuiEvent::mouse_lclk_down))
	{

	}
	if ((ui == (Gui*)options) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
	if ((ui == (Gui*)mainmenu) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::mainmenu);
	}
	if ((ui == (Gui*)quit) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::quitgame);
	}
}