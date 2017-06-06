#include "S_Campaign.h"
#include "j1Player.h"
#include "Gui.h"
#include "j1GameStartMenuBack.h"
#include "j1Render.h"
#include "ParticleManager.h"
#include "j1Window.h"

S_Campaign::S_Campaign()
{
	scene_str = "Campaign";
}

S_Campaign::~S_Campaign()
{
}

bool S_Campaign::Awake(pugi::xml_node& conf)
{
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);

	newcampaign = App->gui->CreateButton(iPoint(X_pos, 200), &std::string("New Campaign"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	newcampaign->SetFont(App->font->Sherwood20);
	((Gui*)newcampaign)->SetListener(this);
	newcampaign->SetVisible(false);
	newcampaign->Focusable(true);

	loadcampaign = App->gui->CreateButton(iPoint(X_pos, 310), &std::string("Load Campaign"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	loadcampaign->SetFont(App->font->Sherwood20);
	((Gui*)loadcampaign)->SetListener(this);
	loadcampaign->SetVisible(false);
	loadcampaign->Focusable(true);

	back = App->gui->CreateButton(iPoint(920, 600), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(newcampaign);
	buttons.push_back(loadcampaign);
	buttons.push_back(back);

	return true;
}

bool S_Campaign::Start()
{
	newcampaign->SetVisible(true);
	loadcampaign->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_Campaign::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_Campaign::Clean()
{
	newcampaign->SetVisible(false);
	loadcampaign->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_Campaign::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)newcampaign) && (event == GuiEvent::mouse_lclk_down))
	{
		App->startmenuback->Freeze(true);
		App->scene->ChangeScene(Scene_ID::startcutscenegame);
		App->scene->Hide();
		App->particlemanager->Enable();
		for (int i = 0; i < App->cutscenemanager->bool_done_cutscenes.size(); i++) {
			App->cutscenemanager->bool_done_cutscenes[i] = false;
		}
		App->player->hearts_containers_test_purpose = 4;
		App->player->half_hearts_test_purpose = 8;

	}
	if ((ui == (Gui*)loadcampaign) && (event == GuiEvent::mouse_lclk_down))
	{
		App->LoadGameModules("save_modules.xml");
	}
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::mainmenu);
	}
}

bool S_Campaign::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_Campaign::Load(pugi::xml_node& node)
{
	return true;
}