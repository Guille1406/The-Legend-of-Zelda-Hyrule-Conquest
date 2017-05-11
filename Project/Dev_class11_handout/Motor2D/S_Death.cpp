#include "S_Death.h"
#include "j1Window.h"
#include "j1Render.h"

S_Death::S_Death()
{
	scene_str = "Death";
}

S_Death::~S_Death()
{
}

bool S_Death::Awake(pugi::xml_node& conf)
{
	Death_Screen_Rect = { 0,0,1280,720 };
	CreditsBack_Rect = { 1278,2061,145,39 };
	CreditsBackHover_Rect = { 1278,2100,145,39 };
	back = App->gui->CreateButton(iPoint(975, 625), &std::string(""), ButtonType::idle_pressed, &CreditsBack_Rect, &CreditsBackHover_Rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(back);

	return true;
};

bool S_Death::Start()
{
	back->SetVisible(true);

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
	back->SetVisible(false);
	return true;
}

void S_Death::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
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