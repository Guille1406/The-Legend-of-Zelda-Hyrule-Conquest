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

bool S_OptionsAudio::Awake()
{
	AudioLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Audio menu"), false);
	AudioLabel->SetFont(App->font->Sherwood28);
	((Gui*)AudioLabel)->SetListener(this);
	AudioLabel->SetVisible(false);
	MasterVolume = App->gui->CreateLabel(iPoint(500, 200), &std::string("Master Volume"), false);
	MasterVolume->SetFont(App->font->Sherwood20);
	((Gui*)MasterVolume)->SetListener(this);
	MasterVolume->SetVisible(false);
	MusicVolume = App->gui->CreateLabel(iPoint(500, 280), &std::string("Music Volume"), false);
	MusicVolume->SetFont(App->font->Sherwood20);
	((Gui*)MusicVolume)->SetListener(this);
	MusicVolume->SetVisible(false);
	SFXVolume = App->gui->CreateLabel(iPoint(500, 360), &std::string("SFX Volume"), false);
	SFXVolume->SetFont(App->font->Sherwood20);
	((Gui*)SFXVolume)->SetListener(this);
	SFXVolume->SetVisible(false);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	return true;
};

bool S_OptionsAudio::Start()
{
	AudioLabel->SetVisible(true);
	MasterVolume->SetVisible(true);
	MusicVolume->SetVisible(true);
	SFXVolume->SetVisible(true);
	back->SetVisible(true);
	return true;
}

bool S_OptionsAudio::Update()
{
	return true;
}

bool S_OptionsAudio::Clean()
{
	AudioLabel->SetVisible(false);
	MasterVolume->SetVisible(false);
	MusicVolume->SetVisible(false);
	SFXVolume->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_OptionsAudio::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}