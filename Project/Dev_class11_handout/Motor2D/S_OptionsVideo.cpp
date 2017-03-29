#include "S_OptionsVideo.h"
#include "Gui.h"
#include "GuiLabel.h"
#include "GuiButton.h"

S_OptionsVideo::S_OptionsVideo()
{
}

S_OptionsVideo::~S_OptionsVideo()
{
}

bool S_OptionsVideo::Awake()
{
	VideoLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Video menu"), false);
	VideoLabel->SetFont(App->font->Sherwood28);
	((Gui*)VideoLabel)->SetListener(this);
	VideoLabel->SetVisible(false);
	scale = App->gui->CreateLabel(iPoint(500, 200), &std::string("Scale"), false);
	scale->SetFont(App->font->Sherwood20);
	((Gui*)scale)->SetListener(this);
	scale->SetVisible(false);
	fullscreen = App->gui->CreateLabel(iPoint(500, 280), &std::string("Fullscreen"), false);
	fullscreen->SetFont(App->font->Sherwood20);
	((Gui*)fullscreen)->SetListener(this);
	fullscreen->SetVisible(false);
	brightness = App->gui->CreateLabel(iPoint(500, 360), &std::string("Brightness"), false);
	brightness->SetFont(App->font->Sherwood20);
	((Gui*)brightness)->SetListener(this);
	brightness->SetVisible(false);
	vsync = App->gui->CreateLabel(iPoint(500, 440), &std::string("VSYNC"), false);
	vsync->SetFont(App->font->Sherwood20);
	((Gui*)vsync)->SetListener(this);
	vsync->SetVisible(false);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	return true;
};

bool S_OptionsVideo::Start()
{
	VideoLabel->SetVisible(true);
	scale->SetVisible(true);
	fullscreen->SetVisible(true);
	brightness->SetVisible(true);
	vsync->SetVisible(true);
	back->SetVisible(true);
	return true;
}

bool S_OptionsVideo::Update()
{
	return true;
}

bool S_OptionsVideo::Clean()
{
	VideoLabel->SetVisible(false);
	scale->SetVisible(false);
	fullscreen->SetVisible(false);
	brightness->SetVisible(false);
	vsync->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_OptionsVideo::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}