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

bool S_OptionsControls::Awake()
{
	ControlsLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Controls menu"), false);
	ControlsLabel->SetFont(App->font->Sherwood28);
	((Gui*)ControlsLabel)->SetListener(this);
	ControlsLabel->SetVisible(false);
	ControllerSensibility = App->gui->CreateLabel(iPoint(500, 200), &std::string("Controller Sensibility"), false);
	ControllerSensibility->SetFont(App->font->Sherwood20);
	((Gui*)ControllerSensibility)->SetListener(this);
	ControllerSensibility->SetVisible(false);
	//ControllerSensibility->Focusable(true);
	ControllerLayout = App->gui->CreateButton(iPoint(500, 280), &std::string("Controller Layout"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	ControllerLayout->SetFont(App->font->Sherwood20);
	((Gui*)ControllerLayout)->SetListener(this);
	ControllerLayout->SetVisible(false);
	ControllerLayout->Focusable(true);
	MouseSensibility = App->gui->CreateLabel(iPoint(500, 360), &std::string("Mouse Sensibility"), false);
	MouseSensibility->SetFont(App->font->Sherwood20);
	((Gui*)MouseSensibility)->SetListener(this);
	MouseSensibility->SetVisible(false);
	//MouseSensibility->Focusable(true);
	MouseLayout = App->gui->CreateButton(iPoint(500, 440), &std::string("Mouse/Keyboard Layout"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MouseLayout->SetFont(App->font->Sherwood20);
	((Gui*)MouseLayout)->SetListener(this);
	MouseLayout->SetVisible(false);
	MouseLayout->Focusable(true);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	//buttons.push_back(ControllerSensibility);
	buttons.push_back(ControllerLayout);
	//buttons.push_back(MouseSensibility);
	buttons.push_back(MouseLayout);
	buttons.push_back(back);

	return true;
};

bool S_OptionsControls::Start()
{
	ControlsLabel->SetVisible(true);
	ControllerSensibility->SetVisible(true);
	ControllerLayout->SetVisible(true);
	MouseSensibility->SetVisible(true);
	MouseLayout->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_OptionsControls::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		std::vector<GuiButton*>::iterator focused_button = std::find(buttons.begin(), buttons.end(), App->gui->GetFocus());
		if ((*focused_button) != buttons.front())
		{
			focused_button--;
			App->gui->SetFocus((*(focused_button)));
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		std::vector<GuiButton*>::iterator focused_button = std::find(buttons.begin(), buttons.end(), App->gui->GetFocus());
		if ((*focused_button) != buttons.back())
		{
			focused_button++;
			App->gui->SetFocus((*(focused_button)));
		}
	}
	return true;
}

bool S_OptionsControls::Clean()
{
	ControlsLabel->SetVisible(false);
	ControllerSensibility->SetVisible(false);
	ControllerLayout->SetVisible(false);
	MouseSensibility->SetVisible(false);
	MouseLayout->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_OptionsControls::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}