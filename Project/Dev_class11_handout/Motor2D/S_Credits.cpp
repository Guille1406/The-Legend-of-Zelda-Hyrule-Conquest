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
	/*
	AudioLabel = App->gui->CreateButton(iPoint(40, 40), &std::string(conf.child("AudioLabel").attribute("value").as_string("Audio menu")), ButtonType::idle_only, &label_title_rec, false);
	AudioLabel->SetFont(App->font->Triforce48);
	((Gui*)AudioLabel)->SetListener(this);
	AudioLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	MasterVolume = App->gui->CreateButton(iPoint(X_pos, 200), &std::string(conf.child("MasterVolume").attribute("value").as_string("Master Volume")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	MasterVolume->SetFont(App->font->Sherwood20);
	((Gui*)MasterVolume)->SetListener(this);
	MasterVolume->SetVisible(false);
	MasterVolume->Focusable(true);
	*/
	CreditsLabel1 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 1"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel1->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel1)->SetListener(this);
	CreditsLabel1->SetVisible(false);

	CreditsLabel2 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 2"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel2->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel2)->SetListener(this);
	CreditsLabel2->SetVisible(false);

	CreditsLabel3 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 3"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel3->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel3)->SetListener(this);
	CreditsLabel3->SetVisible(false);

	CreditsLabel4 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 4"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel4->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel4)->SetListener(this);
	CreditsLabel4->SetVisible(false);

	CreditsLabel5 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 5"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel5->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel5)->SetListener(this);
	CreditsLabel5->SetVisible(false);

	CreditsLabel6 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 6"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel6->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel6)->SetListener(this);
	CreditsLabel6->SetVisible(false);

	CreditsLabel7 = App->gui->CreateButton(iPoint(40, 40), &std::string("Label 7"), ButtonType::idle_only, &label_title_rec, false);
	CreditsLabel7->SetFont(App->font->Triforce48);
	((Gui*)CreditsLabel7)->SetListener(this);
	CreditsLabel7->SetVisible(false);

	GuiButton* CreditsLabel1 = nullptr;
	GuiButton* CreditsLabel2 = nullptr;
	GuiButton* CreditsLabel3 = nullptr;
	GuiButton* CreditsLabel4 = nullptr;
	GuiButton* CreditsLabel5 = nullptr;
	GuiButton* CreditsLabel6 = nullptr;
	GuiButton* CreditsLabel7 = nullptr;


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
	//App->render->DrawQuad({ 0,0,1280,720 }, 39, 39, 39, 255, true, true, false);
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
	MenuInput(&buttons);
	return true;
}

bool S_Credits::Clean()
{
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