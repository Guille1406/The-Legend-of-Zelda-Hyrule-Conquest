#include "S_Credits.h"
#include "j1Window.h"

S_Credits::S_Credits()
{
	scene_str = "Credits";
}

S_Credits::~S_Credits()
{
}

bool S_Credits::Awake(pugi::xml_node& conf)
{
	/*
	AudioLabel = App->gui->CreateButton(iPoint(40, 40), &std::string(conf.child("AudioLabel").attribute("value").as_string("Audio menu")), ButtonType::idle_only, &label_title_rec, false);
	AudioLabel->SetFont(App->font->Triforce48);
	((Gui*)AudioLabel)->SetListener(this);
	AudioLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	MasterVolume = App->gui->CreateButton(iPoint(X_pos, 200), &std::string(conf.child("MasterVolume").attribute("value").as_string("Master Volume")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MasterVolume->SetFont(App->font->Sherwood20);
	((Gui*)MasterVolume)->SetListener(this);
	MasterVolume->SetVisible(false);
	MasterVolume->Focusable(true);
	*/
	/*
	MusicVolume = App->gui->CreateButton(iPoint(X_pos, 310), &std::string(conf.child("MusicVolume").attribute("value").as_string("Music Volume")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MusicVolume->SetFont(App->font->Sherwood20);
	((Gui*)MusicVolume)->SetListener(this);
	MusicVolume->SetVisible(false);
	MusicVolume->Focusable(true);
	SFXVolume = App->gui->CreateButton(iPoint(X_pos, 420), &std::string(conf.child("SFXVolume").attribute("value").as_string("SFX Volume")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	SFXVolume->SetFont(App->font->Sherwood20);
	((Gui*)SFXVolume)->SetListener(this);
	SFXVolume->SetVisible(false);
	SFXVolume->Focusable(true);
	*/
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	//buttons.push_back(MasterVolume);
	//buttons.push_back(MusicVolume);
	//buttons.push_back(SFXVolume);
	buttons.push_back(back);

	return true;
};

bool S_Credits::Start()
{
	//AudioLabel->SetVisible(true);
	//MasterVolume->SetVisible(true);
	//MusicVolume->SetVisible(true);
	//SFXVolume->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_Credits::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_Credits::Clean()
{
	//AudioLabel->SetVisible(false);
	//MasterVolume->SetVisible(false);
	//MusicVolume->SetVisible(false);
	//SFXVolume->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_Credits::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::mainmenu);
	}
}

bool S_Credits::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_Credits::Load(pugi::xml_node& node)
{
	return true;
}