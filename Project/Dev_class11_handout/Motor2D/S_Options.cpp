#include "S_Options.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"
#include "j1Window.h"

S_Options::S_Options()
{
}

S_Options::~S_Options()
{
}

bool S_Options::Start()
{
	OptionsLabel = App->gui->CreateLabel(iPoint(200, 100), &std::string("Options menu"), false);
	OptionsLabel->SetFont(App->font->Sherwood28);
	((Gui*)OptionsLabel)->SetListener(this);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	controls = App->gui->CreateButton(iPoint(X_pos, 200), &std::string("Controls Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	controls->SetFont(App->font->Sherwood20);
	((Gui*)controls)->SetListener(this);
	video = App->gui->CreateButton(iPoint(X_pos, 310), &std::string("Video Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	video->SetFont(App->font->Sherwood20);
	((Gui*)video)->SetListener(this);
	audio = App->gui->CreateButton(iPoint(X_pos, 420), &std::string("Audio Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	audio->SetFont(App->font->Sherwood20);
	((Gui*)audio)->SetListener(this);
	gameplay = App->gui->CreateButton(iPoint(X_pos, 530), &std::string("Gameplay Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	gameplay->SetFont(App->font->Sherwood20);
	((Gui*)gameplay)->SetListener(this);
	back = App->gui->CreateButton(iPoint(920, 600), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);

	return true;
}

bool S_Options::Update()
{
	return true;
}

bool S_Options::Clean()
{
	return true;
}

void S_Options::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)controls) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::optionscontrols);
	}
	if ((ui == (Gui*)video) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::optionsvideo);
	}
	if ((ui == (Gui*)audio) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::optionsaudio);
	}
	if ((ui == (Gui*)gameplay) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::optionsgameplay);
	}
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::mainmenu);
	}
}