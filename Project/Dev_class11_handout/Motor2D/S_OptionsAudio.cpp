#include "S_OptionsAudio.h"
#include "j1Window.h"

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
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	MasterVolume = App->gui->CreateButton(iPoint(X_pos, 200), &std::string("Master Volume"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MasterVolume->SetFont(App->font->Sherwood20);
	((Gui*)MasterVolume)->SetListener(this);
	MasterVolume->SetVisible(false);
	MasterVolume->Focusable(true);
	MusicVolume = App->gui->CreateButton(iPoint(X_pos, 310), &std::string("Music Volume"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MusicVolume->SetFont(App->font->Sherwood20);
	((Gui*)MusicVolume)->SetListener(this);
	MusicVolume->SetVisible(false);
	MusicVolume->Focusable(true);
	SFXVolume = App->gui->CreateButton(iPoint(X_pos, 420), &std::string("SFX Volume"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	SFXVolume->SetFont(App->font->Sherwood20);
	((Gui*)SFXVolume)->SetListener(this);
	SFXVolume->SetVisible(false);
	SFXVolume->Focusable(true);
	back = App->gui->CreateButton(iPoint(920, 600), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(MasterVolume);
	buttons.push_back(MusicVolume);
	buttons.push_back(SFXVolume);
	buttons.push_back(back);

	return true;
};

bool S_OptionsAudio::Start()
{
	AudioLabel->SetVisible(true);
	MasterVolume->SetVisible(true);
	MusicVolume->SetVisible(true);
	SFXVolume->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_OptionsAudio::Update()
{
	MenuInput(&buttons);
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