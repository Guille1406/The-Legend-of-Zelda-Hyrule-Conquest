#include "S_OptionsControls.h"
#include "j1Window.h"
#include "j1InputManager.h"

S_OptionsControls::S_OptionsControls()
{
	scene_str = "OptionsControls";
}

S_OptionsControls::~S_OptionsControls()
{
}

bool S_OptionsControls::Awake(pugi::xml_node& conf)
{
	controller_layout_normal_rect = { 443,2604,450,450 };
	controller_layout_alternative_rect = { 0, 2604, 443, 450 };

	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	ControlsLabel = App->gui->CreateButton(iPoint(40, 40), &std::string(conf.child("ControlsLabel").attribute("value").as_string("Controls menu")), ButtonType::idle_only, &label_title_rec, false);
	ControlsLabel->SetFont(App->font->Triforce48);
	((Gui*)ControlsLabel)->SetListener(this);
	ControlsLabel->SetVisible(false);
	ControllerAlternative = App->gui->CreateButton(iPoint(X_pos - 100, 150), &std::string("Altern. Controller Layout"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	ControllerAlternative->SetFont(App->font->Sherwood20);
	((Gui*)ControllerAlternative)->SetListener(this);
	ControllerAlternative->SetVisible(false);
	ControllerAlternative->Focusable(true);
	ControllerAlternative_check = App->gui->CreateCheck(iPoint(X_pos + 275, 179), &idle_check_rect, &pressed_check_rect);
	((Gui*)ControllerAlternative_check)->SetListener(this);
	ControllerAlternative_check->SetVisible(false);
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	X_pos = App->win->GetWindowWHalf() - (int)(controller_layout_normal_rect.w * 0.5f);

	controller_layout_normal = App->gui->CreateImage(iPoint(X_pos, 270), &controller_layout_normal_rect, false);
	((Gui*)controller_layout_normal)->SetListener(this);
	controller_layout_normal->SetVisible(false);

	controller_layout_alternative = App->gui->CreateImage(iPoint(X_pos, 270), &controller_layout_alternative_rect, false);
	((Gui*)controller_layout_alternative)->SetListener(this);
	controller_layout_alternative->SetVisible(false);

	buttons.push_back(ControllerAlternative);
	buttons.push_back(back);

	return true;
};

bool S_OptionsControls::Start()
{
	ControlsLabel->SetVisible(true);
	ControllerAlternative->SetVisible(true);
	ControllerAlternative_check->SetVisible(true);
	back->SetVisible(true);

	if(alternative_active)
		controller_layout_alternative->SetVisible(true);
	else
		controller_layout_normal->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_OptionsControls::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_OptionsControls::Clean()
{
	ControlsLabel->SetVisible(false);
	ControllerAlternative->SetVisible(false);
	ControllerAlternative_check->SetVisible(false);
	back->SetVisible(false);

	controller_layout_normal->SetVisible(false);
	controller_layout_alternative->SetVisible(false);

	return true;
}

void S_OptionsControls::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)ControllerAlternative) && (event == GuiEvent::mouse_lclk_down))
	{
		ControllerAlternative_check->ChangeState();
		App->inputM->ChangeInput();
		alternative_active = !alternative_active;

		if (alternative_active)
		{
			controller_layout_normal->SetVisible(false);
			controller_layout_alternative->SetVisible(true);
		}
		else
		{
			controller_layout_normal->SetVisible(true);
			controller_layout_alternative->SetVisible(false);
		}

	}

	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::options);
	}
}

bool S_OptionsControls::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_OptionsControls::Load(pugi::xml_node& node)
{
	return true;
}