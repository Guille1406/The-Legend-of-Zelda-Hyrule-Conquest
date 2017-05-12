#include "S_Death.h"
#include "j1Window.h"
#include "j1Render.h"
#include"j1GameStartMenuBack.h"
#include"Particle.h"
S_Death::S_Death()
{
	scene_str = "Death";
}

S_Death::~S_Death()
{
}

bool S_Death::Awake(pugi::xml_node& conf)
{
	int X_pos = 0;
	Death_Screen_Rect = { 0,0,1280,720 };

	DeathTryAgain_Rect = { 1278,1940,229,30 };
	DeathTryAgainHover_Rect = { 1278,1971,229,30 };

	X_pos = App->win->GetWindowWHalf() - (int)(DeathTryAgain_Rect.w * 0.5f);
	DeathTryAgain = App->gui->CreateButton(iPoint(X_pos, 350), &std::string(""), ButtonType::idle_hover, &DeathTryAgainHover_Rect, &DeathTryAgain_Rect, false);
	((Gui*)DeathTryAgain)->SetListener(this);
	DeathTryAgain->SetVisible(false);
	DeathTryAgain->Focusable(true);
	buttons.push_back(DeathTryAgain);

	DeathMainMenu_Rect = { 1278,2001,250,30 };
	DeathMainMenuHover_Rect = { 1278,2031,250,30 };

	X_pos = App->win->GetWindowWHalf() - (int)(DeathMainMenu_Rect.w * 0.5f);
	DeathMainMenu = App->gui->CreateButton(iPoint(X_pos, 400), &std::string(""), ButtonType::idle_hover, &DeathMainMenuHover_Rect, &DeathMainMenu_Rect, false);
	((Gui*)DeathMainMenu)->SetListener(this);
	DeathMainMenu->SetVisible(false);
	DeathMainMenu->Focusable(true);
	buttons.push_back(DeathMainMenu);

	return true;
};

bool S_Death::Start()
{
	DeathTryAgain->SetVisible(true);
	DeathMainMenu->SetVisible(true);

	Death_Screen = App->gui->CreateImage(iPoint(0, 0), &Death_Screen_Rect, false, AddGuiTo::none);

	App->gui->SetFocus(buttons.front());
	return true;
}

bool S_Death::Update()
{
	//App->render->DrawQuad({ 0,0,1280,720 }, 39, 39, 39, 255, true, true, false);
	Death_Screen->DrawWithAlternativeAtlas(App->scene->GetDeath_Scene_Atlas());
	MenuInput(&buttons);
	return true;
}

bool S_Death::Clean()
{
	delete Death_Screen;
	DeathTryAgain->SetVisible(false);
	DeathMainMenu->SetVisible(true);
	return true;
}

void S_Death::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)DeathTryAgain) && (event == GuiEvent::mouse_lclk_down))
	{
		App->startmenuback->Freeze(true);
		App->LoadGameModules("save_modules.xml");
		//App->scene->Hide();
		App->particlemanager->Enable();
	}
	if ((ui == (Gui*)DeathMainMenu) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::mainmenu);
	}
}

bool S_Death::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_Death::Load(pugi::xml_node& node)
{
	return true;
}