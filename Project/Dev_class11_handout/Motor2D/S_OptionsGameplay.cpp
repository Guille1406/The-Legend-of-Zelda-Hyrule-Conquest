#include "S_OptionsGameplay.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_OptionsGameplay::S_OptionsGameplay()
{
}

S_OptionsGameplay::~S_OptionsGameplay()
{
}

bool S_OptionsGameplay::Start()
{
	GameplayLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Gameplay menu"), false);
	GameplayLabel->SetFont(App->font->Sherwood28);
	((Gui*)GameplayLabel)->SetListener(this);
	ShowhideHUD = App->gui->CreateLabel(iPoint(500, 200), &std::string("Toggle HUD visibility"), false);
	ShowhideHUD->SetFont(App->font->Sherwood20);
	((Gui*)ShowhideHUD)->SetListener(this);
	Language = App->gui->CreateButton(iPoint(500, 280), &std::string("Language"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Language->SetFont(App->font->Sherwood20);
	((Gui*)Language)->SetListener(this);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	return true;
}

bool S_OptionsGameplay::Update()
{
	return true;
}

bool S_OptionsGameplay::Clean()
{
	return true;
}

void S_OptionsGameplay::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}