#include "S_Credits.h"
#include "j1Window.h"
#include "j1Render.h"

S_Credits::S_Credits()
{
	scene_str = "Credits";
}

S_Credits::~S_Credits()
{
}

bool S_Credits::Awake(pugi::xml_node& conf)
{
	CreditsLogo_Rect = { 0,0,1280,720 };
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

bool S_Credits::Start()
{
	back->SetVisible(true);

	CreditsLogo = App->gui->CreateImage(iPoint(0, 0), &CreditsLogo_Rect, false, AddGuiTo::none);

	App->gui->SetFocus(buttons.front());
	return true;
}

bool S_Credits::Update()
{
	//App->render->DrawQuad({ 0,0,1280,720 }, 39, 39, 39, 255, true, true, false);
	CreditsLogo->DrawWithAlternativeAtlas(App->scene->GetCredits_Logo_Atlas());
	MenuInput(&buttons);
	return true;
}

bool S_Credits::Clean()
{
	delete CreditsLogo;
	back->SetVisible(false);
	return true;
}

void S_Credits::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		//App->scene->Show(Scene_ID::mainmenu);
		App->scene->Hide();
	}
}

bool S_Credits::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_Credits::Load(pugi::xml_node& node)
{
	return true;
}