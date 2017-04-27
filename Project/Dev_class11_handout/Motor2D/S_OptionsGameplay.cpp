#include "S_OptionsGameplay.h"
#include "j1Window.h"
#include "j1HUD.h"

S_OptionsGameplay::S_OptionsGameplay()
{
	scene_str = "OptionsGameplay";
}

S_OptionsGameplay::~S_OptionsGameplay()
{
}

bool S_OptionsGameplay::Awake(pugi::xml_node& conf)
{
	GameplayLabel = App->gui->CreateButton(iPoint(40, 40), &std::string(conf.child("GameplayLabel").attribute("value").as_string("Gameplay menu")), ButtonType::idle_only, &label_title_rec, false);
	GameplayLabel->SetFont(App->font->Triforce48);
	((Gui*)GameplayLabel)->SetListener(this);
	GameplayLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	int offset = -100;
	ShowhideHUD = App->gui->CreateButton(iPoint(X_pos + offset, 200), &std::string(conf.child("ShowhideHUD").attribute("value").as_string("Toggle HUD visibility")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	ShowhideHUD->SetFont(App->font->Sherwood20);
	((Gui*)ShowhideHUD)->SetListener(this);
	ShowhideHUD->SetVisible(false);
	ShowhideHUD->Focusable(true);
	ShowhideHUD_check = App->gui->CreateCheck(iPoint(X_pos + 275, 229), &idle_check_rect, &pressed_check_rect);
	((Gui*)ShowhideHUD_check)->SetListener(this);
	ShowhideHUD_check->SetVisible(false);
	ShowhideHUD_check->ChangeState();
	Language = App->gui->CreateButton(iPoint(X_pos + offset, 310), &std::string(conf.child("Language").attribute("value").as_string("Language")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Language->SetFont(App->font->Sherwood20);
	((Gui*)Language)->SetListener(this);
	Language->SetVisible(false);
	Language->Focusable(true);
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(ShowhideHUD);
	buttons.push_back(Language);
	buttons.push_back(back);

	return true;
};

bool S_OptionsGameplay::Start()
{
	GameplayLabel->SetVisible(true);
	ShowhideHUD->SetVisible(true);
	Language->SetVisible(true);
	back->SetVisible(true);
	ShowhideHUD_check->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_OptionsGameplay::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_OptionsGameplay::Clean()
{
	GameplayLabel->SetVisible(false);
	ShowhideHUD->SetVisible(false);
	Language->SetVisible(false);
	back->SetVisible(false);
	ShowhideHUD_check->SetVisible(false);
	return true;
}

void S_OptionsGameplay::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)ShowhideHUD) && (event == GuiEvent::mouse_lclk_down))
	{
		ShowhideHUD_check->ChangeState();
		if (ShowhideHUD_check->Checked())
			App->hud->ToggleVisibility(true);
		else
			App->hud->ToggleVisibility(false);
	}
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::options);
	}
}

bool S_OptionsGameplay::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_OptionsGameplay::Load(pugi::xml_node& node)
{
	return true;
}