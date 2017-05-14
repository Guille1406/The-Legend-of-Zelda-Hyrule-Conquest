#include "S_QuitGame.h"
#include "j1Player.h"
#include "j1Window.h"
#include "S_InGameMenu.h"

S_QuitGame::S_QuitGame()
{
	scene_str = "QuitGame";
}

S_QuitGame::~S_QuitGame()
{
}

bool S_QuitGame::Awake(pugi::xml_node& conf)
{
	Label = App->gui->CreateButton(iPoint(App->win->GetWindowWHalf() - (int)(background.w * 0.5f), 200), &std::string(conf.child("Label").attribute("value").as_string("Are you sure you want to quit?")), ButtonType::idle_only, &background, false);
	Label->SetFont(App->font->Triforce48);
	((Gui*)Label)->SetListener(this);
	Label->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	Yes = App->gui->CreateButton(iPoint(X_pos, 320), &std::string(conf.child("Yes").attribute("value").as_string("Yes")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Yes->SetFont(App->font->Sherwood20);
	((Gui*)Yes)->SetListener(this);
	Yes->SetVisible(false);
	Yes->Focusable(true);
	No = App->gui->CreateButton(iPoint(X_pos, 430), &std::string(conf.child("No").attribute("value").as_string("No")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	No->SetFont(App->font->Sherwood20);
	((Gui*)No)->SetListener(this);
	No->SetVisible(false);
	No->Focusable(true);

	/*
	Yes = App->gui->CreateButton(iPoint(X_pos - 200, 350), &std::string(conf.child("Yes").attribute("value").as_string("Yes")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Yes->SetFont(App->font->Sherwood20);
	((Gui*)Yes)->SetListener(this);
	Yes->SetVisible(false);
	Yes->Focusable(true);
	No = App->gui->CreateButton(iPoint(X_pos + 200, 350), &std::string(conf.child("No").attribute("value").as_string("No")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	No->SetFont(App->font->Sherwood20);
	((Gui*)No)->SetListener(this);
	No->SetVisible(false);
	No->Focusable(true);
	*/

	buttons.push_back(Yes);
	buttons.push_back(No);

	return true;
}

bool S_QuitGame::Start()
{
	Label->SetVisible(true);
	Yes->SetVisible(true);
	No->SetVisible(true);

	App->gui->SetFocus(No);

	return true;
}

bool S_QuitGame::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_QuitGame::Clean()
{
	Label->SetVisible(false);
	Yes->SetVisible(false);
	No->SetVisible(false);
	return true;
}

void S_QuitGame::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)Yes) && (event == GuiEvent::mouse_lclk_down))
	{
		App->WantToQuit();
	}

	if ((ui == (Gui*)No) && (event == GuiEvent::mouse_lclk_down))
	{
		if (((S_InGameMenu*)App->scene->InGameMenuScene())->Active())
			App->scene->Show(Scene_ID::ingamemenu);
		else
			App->scene->Show(Scene_ID::mainmenu);
	}
}

bool S_QuitGame::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_QuitGame::Load(pugi::xml_node& node)
{
	return true;
}