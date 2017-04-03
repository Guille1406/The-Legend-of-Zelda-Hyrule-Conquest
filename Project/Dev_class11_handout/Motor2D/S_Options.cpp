#include "S_Options.h"
#include "j1Window.h"
#include "S_InGameMenu.h"

S_Options::S_Options()
{
	scene_str = "Options";
}

S_Options::~S_Options()
{
}

bool S_Options::Awake(pugi::xml_node& conf)
{
	OptionsLabel = App->gui->CreateLabel(iPoint(200, 100), &std::string(conf.child("OptionsLabel").attribute("value").as_string("Options menu")), false);
	OptionsLabel->SetFont(App->font->Sherwood28);
	((Gui*)OptionsLabel)->SetListener(this);
	OptionsLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	controls = App->gui->CreateButton(iPoint(X_pos, 200), &std::string(conf.child("controls").attribute("value").as_string("Controls Settings")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	controls->SetFont(App->font->Sherwood20);
	((Gui*)controls)->SetListener(this);
	controls->SetVisible(false);
	controls->Focusable(true);
	video = App->gui->CreateButton(iPoint(X_pos, 310), &std::string(conf.child("video").attribute("value").as_string("Video Settings")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	video->SetFont(App->font->Sherwood20);
	((Gui*)video)->SetListener(this);
	video->SetVisible(false);
	video->Focusable(true);
	audio = App->gui->CreateButton(iPoint(X_pos, 420), &std::string(conf.child("audio").attribute("value").as_string("Audio Settings")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	audio->SetFont(App->font->Sherwood20);
	((Gui*)audio)->SetListener(this);
	audio->SetVisible(false);
	audio->Focusable(true);
	gameplay = App->gui->CreateButton(iPoint(X_pos, 530), &std::string(conf.child("gameplay").attribute("value").as_string("Gameplay Settings")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	gameplay->SetFont(App->font->Sherwood20);
	((Gui*)gameplay)->SetListener(this);
	gameplay->SetVisible(false);
	gameplay->Focusable(true);
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(controls);
	buttons.push_back(video);
	buttons.push_back(audio);
	buttons.push_back(gameplay);
	buttons.push_back(back);

	return true;
};

bool S_Options::Start()
{
	OptionsLabel->SetVisible(true);
	controls->SetVisible(true);
	video->SetVisible(true);
	audio->SetVisible(true);
	gameplay->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	const MainScene* Prev = App->scene->GetPreviousScene();
	if((Prev->scene_name == Scene_ID::mainmenu) || (Prev->scene_name == Scene_ID::ingamemenu))
		PreviousScene = Prev;

	return true;
}

bool S_Options::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_Options::Clean()
{
	OptionsLabel->SetVisible(false);
	controls->SetVisible(false);
	video->SetVisible(false);
	audio->SetVisible(false);
	gameplay->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_Options::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)controls) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::optionscontrols);
	}
	if ((ui == (Gui*)video) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::optionsvideo);
	}
	if ((ui == (Gui*)audio) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::optionsaudio);
	}
	if ((ui == (Gui*)gameplay) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::optionsgameplay);
	}
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		if (((S_InGameMenu*)App->scene->InGameMenuScene())->Active())
			App->scene->Show(Scene_ID::ingamemenu);
		else
			App->scene->Show(Scene_ID::mainmenu);
	}
}