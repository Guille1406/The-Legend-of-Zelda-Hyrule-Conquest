#include "S_QuitGame.h"
#include "j1Player.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_QuitGame::S_QuitGame()
{
}

S_QuitGame::~S_QuitGame()
{
}

bool S_QuitGame::Start()
{
	App->player->Disable();
	Label = App->gui->CreateLabel(iPoint(500, 200), &std::string("Are you sure you want to quit?"), false);
	Label->SetFont(App->font->Sherwood28);
	((Gui*)Label)->SetListener(this);
	Yes = App->gui->CreateButton(iPoint(350, 250), &std::string("Yes"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Yes->SetFont(App->font->Sherwood20);
	((Gui*)Yes)->SetListener(this);
	No = App->gui->CreateButton(iPoint(650, 250), &std::string("No"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	No->SetFont(App->font->Sherwood20);
	((Gui*)No)->SetListener(this);
	return true;
}

bool S_QuitGame::Update()
{
	return true;
}

bool S_QuitGame::Clean()
{
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