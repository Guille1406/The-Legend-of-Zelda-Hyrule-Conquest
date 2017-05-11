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
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(back);

	return true;
};

bool S_Credits::Start()
{
	CreditsLogo = App->gui->CreateImage(iPoint( 0, 0), &CreditsLogo_Rect, false, AddGuiTo::none);
	back->SetVisible(true);
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
		App->scene->Show(Scene_ID::mainmenu);
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