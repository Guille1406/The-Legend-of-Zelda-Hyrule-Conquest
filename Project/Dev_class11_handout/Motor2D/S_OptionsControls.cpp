#include "S_OptionsControls.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_OptionsControls::S_OptionsControls()
{
}

S_OptionsControls::~S_OptionsControls()
{
}

bool S_OptionsControls::Start()
{
	SDL_Rect idle_button_rect = { 410,165,231,73 };
	SDL_Rect hover_button_rect = { -1,109,231,73 };
	SDL_Rect pressed_button_rect = { 641,165,231,73 };
	ControlsLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Controls menu"), false);
	ControlsLabel->SetFont(App->font->Sherwood28);
	((Gui*)ControlsLabel)->SetListener(this);
	ControllerSensibility = App->gui->CreateLabel(iPoint(500, 200), &std::string("Controller Sensibility"), false);
	ControllerSensibility->SetFont(App->font->Sherwood20);
	((Gui*)ControllerSensibility)->SetListener(this);
	ControllerLayout = App->gui->CreateButton(iPoint(500, 280), &std::string("Controller Layout"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	ControllerLayout->SetFont(App->font->Sherwood20);
	((Gui*)ControllerLayout)->SetListener(this);
	MouseSensibility = App->gui->CreateLabel(iPoint(500, 360), &std::string("Mouse Sensibility"), false);
	MouseSensibility->SetFont(App->font->Sherwood20);
	((Gui*)MouseSensibility)->SetListener(this);
	MouseLayout = App->gui->CreateButton(iPoint(500, 440), &std::string("Mouse/Keyboard Layout"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MouseLayout->SetFont(App->font->Sherwood20);
	((Gui*)MouseLayout)->SetListener(this);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	return true;
}

bool S_OptionsControls::Update()
{
	return true;
}

bool S_OptionsControls::Clean()
{
	return true;
}

void S_OptionsControls::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}