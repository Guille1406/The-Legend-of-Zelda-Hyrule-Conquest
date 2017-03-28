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

bool S_OptionsVideo::Start()
{
	VideoLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string("Video menu"), false);
	VideoLabel->SetFont(App->font->Sherwood28);
	((Gui*)VideoLabel)->SetListener(this);

	VideoLabel = App->gui->CreateLabel(iPoint(500, 200), &std::string("Scale"), false);
	VideoLabel->SetFont(App->font->Sherwood20);
	((Gui*)VideoLabel)->SetListener(this);

	VideoLabel = App->gui->CreateLabel(iPoint(500, 280), &std::string("Fullscreen"), false);
	VideoLabel->SetFont(App->font->Sherwood20);
	((Gui*)VideoLabel)->SetListener(this);

	VideoLabel = App->gui->CreateLabel(iPoint(500, 360), &std::string("Brightness"), false);
	VideoLabel->SetFont(App->font->Sherwood20);
	((Gui*)VideoLabel)->SetListener(this);

	VideoLabel = App->gui->CreateLabel(iPoint(500, 440), &std::string("VSYNC"), false);
	VideoLabel->SetFont(App->font->Sherwood20);
	((Gui*)VideoLabel)->SetListener(this);

	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	return true;
}

bool S_OptionsVideo::Update()
{
	return true;
}

bool S_OptionsVideo::Clean()
{
	return true;
}

void S_OptionsVideo::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::options);
	}
}