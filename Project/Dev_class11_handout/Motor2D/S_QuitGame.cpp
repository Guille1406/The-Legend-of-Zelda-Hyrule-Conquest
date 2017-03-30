#include "S_QuitGame.h"
#include "j1Player.h"
#include "j1Window.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_QuitGame::S_QuitGame()
{
}

S_QuitGame::~S_QuitGame()
{
}

bool S_QuitGame::Awake()
{
	Label = App->gui->CreateButton(iPoint(App->win->GetWindowWHalf() - (int)(background.w * 0.5f), 200), &std::string("Are you sure you want to quit?"), ButtonType::idle_only, &background, false);
	Label->SetFont(App->font->Sherwood28);
	((Gui*)Label)->SetListener(this);
	Label->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	Yes = App->gui->CreateButton(iPoint(X_pos - 200, 350), &std::string("Yes"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Yes->SetFont(App->font->Sherwood20);
	((Gui*)Yes)->SetListener(this);
	Yes->SetVisible(false);
	No = App->gui->CreateButton(iPoint(X_pos + 200, 350), &std::string("No"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	No->SetFont(App->font->Sherwood20);
	((Gui*)No)->SetListener(this);
	No->SetVisible(false);
	return true;
}

bool S_QuitGame::Start()
{
	App->player->Disable();
	Label->SetVisible(true);
	Yes->SetVisible(true);
	No->SetVisible(true);
	return true;
}

bool S_QuitGame::Update()
{
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
		App->scene->ChangeScene(Scene_ID::mainmenu);
	}
}