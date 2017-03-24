#include "S_OptionsAudio.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_OptionsAudio::S_OptionsAudio()
{
}

S_OptionsAudio::~S_OptionsAudio()
{
}

bool S_OptionsAudio::Start()
{
	SDL_Rect idle_button_rect = { 410,165,231,73 };
	SDL_Rect hover_button_rect = { -1,109,231,73 };
	SDL_Rect pressed_button_rect = { 641,165,231,73 };
	AudioLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Audio menu"), false);
	AudioLabel->SetFont(App->font->Sherwood28);
	((Gui*)AudioLabel)->SetListener(this);
	MasterVolume = App->gui->CreateLabel(iPoint(500, 200), &std::string("Master Volume"), false);
	MasterVolume->SetFont(App->font->Sherwood20);
	((Gui*)MasterVolume)->SetListener(this);
	MusicVolume = App->gui->CreateLabel(iPoint(500, 280), &std::string("Music Volume"), false);
	MusicVolume->SetFont(App->font->Sherwood20);
	((Gui*)MusicVolume)->SetListener(this);
	SFXVolume = App->gui->CreateLabel(iPoint(500, 360), &std::string("SFX Volume"), false);
	SFXVolume->SetFont(App->font->Sherwood20);
	((Gui*)SFXVolume)->SetListener(this);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	return true;
}

bool S_OptionsAudio::Update()
{
	return true;
}

bool S_OptionsAudio::Clean()
{
	return true;
}

void S_OptionsAudio::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}