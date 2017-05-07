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
	int X_pos = App->win->GetWindowWHalf() - (int)(label_title_rec.w * 0.5f);

	CreditsLabel1 = App->gui->CreateButton(iPoint(X_pos, 31), &std::string("Lead - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel1->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel1)->SetListener(this);
	CreditsLabel1->SetVisible(false);

	CreditsLabel2 = App->gui->CreateButton(iPoint(X_pos, 125), &std::string("Management - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel2->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel2)->SetListener(this);
	CreditsLabel2->SetVisible(false);

	CreditsLabel3 = App->gui->CreateButton(iPoint(X_pos, 219), &std::string("Art - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel3->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel3)->SetListener(this);
	CreditsLabel3->SetVisible(false);

	CreditsLabel4 = App->gui->CreateButton(iPoint(X_pos, 313), &std::string("Code - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel4->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel4)->SetListener(this);
	CreditsLabel4->SetVisible(false);

	CreditsLabel5 = App->gui->CreateButton(iPoint(X_pos, 407), &std::string("UI - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel5->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel5)->SetListener(this);
	CreditsLabel5->SetVisible(false);

	CreditsLabel6 = App->gui->CreateButton(iPoint(X_pos, 501), &std::string("QA - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel6->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel6)->SetListener(this);
	CreditsLabel6->SetVisible(false);

	CreditsLabel7 = App->gui->CreateButton(iPoint(X_pos, 595), &std::string("Game Design - "), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel7->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel7)->SetListener(this);
	CreditsLabel7->SetVisible(false);

	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	CreditsLogo_Rect = { 0,0,550,360 };
	
	buttons.push_back(back);

	return true;
};

bool S_Credits::Start()
{
	CreditsLogo = App->gui->CreateImage(iPoint(0, 0), &CreditsLogo_Rect, false);

	CreditsLabel1->SetVisible(true);
	CreditsLabel2->SetVisible(true);
	CreditsLabel3->SetVisible(true);
	CreditsLabel4->SetVisible(true);
	CreditsLabel5->SetVisible(true);
	CreditsLabel6->SetVisible(true);
	CreditsLabel7->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_Credits::Update()
{
	CreditsLogo->DrawWithAlternativeAtlas(App->scene->GetCredits_Logo_Atlas());
	MenuInput(&buttons);
	return true;
}

bool S_Credits::Clean()
{
	delete CreditsLogo;
	CreditsLabel1->SetVisible(false);
	CreditsLabel2->SetVisible(false);
	CreditsLabel3->SetVisible(false);
	CreditsLabel4->SetVisible(false);
	CreditsLabel5->SetVisible(false);
	CreditsLabel6->SetVisible(false);
	CreditsLabel7->SetVisible(false);
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