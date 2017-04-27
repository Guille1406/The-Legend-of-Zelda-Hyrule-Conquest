#include "S_OptionsControls.h"
#include "j1Window.h"

S_OptionsControls::S_OptionsControls()
{
	scene_str = "OptionsControls";
}

S_OptionsControls::~S_OptionsControls()
{
}

bool S_OptionsControls::Awake(pugi::xml_node& conf)
{
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	ControlsLabel = App->gui->CreateButton(iPoint(40, 40), &std::string(conf.child("ControlsLabel").attribute("value").as_string("Controls menu")), ButtonType::idle_only, &label_title_rec, false);
	ControlsLabel->SetFont(App->font->Triforce48);
	((Gui*)ControlsLabel)->SetListener(this);
	ControlsLabel->SetVisible(false);
	ControllerLayout = App->gui->CreateButton(iPoint(X_pos, 200), &std::string(conf.child("ControllerLayout").attribute("value").as_string("Controller Layout")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	ControllerLayout->SetFont(App->font->Sherwood20);
	((Gui*)ControllerLayout)->SetListener(this);
	ControllerLayout->SetVisible(false);
	ControllerLayout->Focusable(true);
	MouseLayout = App->gui->CreateButton(iPoint(X_pos, 310), &std::string(conf.child("MouseLayout").attribute("value").as_string("Mouse/Keyboard Layout")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MouseLayout->SetFont(App->font->Sherwood20);
	((Gui*)MouseLayout)->SetListener(this);
	MouseLayout->SetVisible(false);
	MouseLayout->Focusable(true);
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(ControllerLayout);
	buttons.push_back(MouseLayout);
	buttons.push_back(back);

	return true;
};

bool S_OptionsControls::Start()
{
	ControlsLabel->SetVisible(true);
	ControllerLayout->SetVisible(true);
	MouseLayout->SetVisible(true);
	back->SetVisible(true);

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
	ControllerLayout->SetVisible(false);
	MouseLayout->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_OptionsControls::OnGui(Gui* ui, GuiEvent event)
{
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