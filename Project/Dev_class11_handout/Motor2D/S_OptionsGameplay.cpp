#include "S_OptionsGameplay.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_OptionsGameplay::S_OptionsGameplay()
{
}

S_OptionsGameplay::~S_OptionsGameplay()
{
}

bool S_OptionsGameplay::Awake()
{
	GameplayLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Gameplay menu"), false);
	GameplayLabel->SetFont(App->font->Sherwood28);
	((Gui*)GameplayLabel)->SetListener(this);
	GameplayLabel->SetVisible(false);
	ShowhideHUD = App->gui->CreateLabel(iPoint(500, 200), &std::string("Toggle HUD visibility"), false);
	ShowhideHUD->SetFont(App->font->Sherwood20);
	((Gui*)ShowhideHUD)->SetListener(this);
	ShowhideHUD->SetVisible(false);
	//back->Focusable(true);
	Language = App->gui->CreateButton(iPoint(500, 280), &std::string("Language"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	Language->SetFont(App->font->Sherwood20);
	((Gui*)Language)->SetListener(this);
	Language->SetVisible(false);
	Language->Focusable(true);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	//buttons.push_back(ShowhideHUD);
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

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_OptionsGameplay::Update()
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

bool S_OptionsGameplay::Clean()
{
	GameplayLabel->SetVisible(false);
	ShowhideHUD->SetVisible(false);
	Language->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_OptionsGameplay::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}