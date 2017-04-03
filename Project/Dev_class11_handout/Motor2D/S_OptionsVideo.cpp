#include "S_OptionsVideo.h"
#include "j1Window.h"

S_OptionsVideo::S_OptionsVideo()
{
	scene_str = "OptionsVideo";
}

S_OptionsVideo::~S_OptionsVideo()
{
}

bool S_OptionsVideo::Awake(pugi::xml_node& conf)
{
	VideoLabel = App->gui->CreateLabel(iPoint(300, 100), &std::string(conf.child("VideoLabel").attribute("value").as_string("Video menu")), false);
	VideoLabel->SetFont(App->font->Sherwood28);
	((Gui*)VideoLabel)->SetListener(this);
	VideoLabel->SetVisible(false);
	int X_pos = App->win->GetWindowWHalf() - (int)(idle_button_rect.w * 0.5f);
	int offset = -100;
	scale = App->gui->CreateButton(iPoint(X_pos + offset, 200), &std::string(conf.child("scale").attribute("value").as_string("Scale")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	scale->SetFont(App->font->Sherwood20);
	((Gui*)scale)->SetListener(this);
	scale->SetVisible(false);
	scale->Focusable(true);
	fullscreen = App->gui->CreateButton(iPoint(X_pos + offset, 310), &std::string(conf.child("fullscreen").attribute("value").as_string("Fullscreen")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	fullscreen->SetFont(App->font->Sherwood20);
	((Gui*)fullscreen)->SetListener(this);
	fullscreen->SetVisible(false);
	fullscreen->Focusable(true);
	fullscreen_check = App->gui->CreateCheck(iPoint(X_pos + 275, 339), &idle_check_rect, &pressed_check_rect);
	((Gui*)fullscreen_check)->SetListener(this);
	fullscreen_check->SetVisible(false);
	brightness = App->gui->CreateButton(iPoint(X_pos + offset, 420), &std::string(conf.child("brightness").attribute("value").as_string("Brightness")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	brightness->SetFont(App->font->Sherwood20);
	((Gui*)brightness)->SetListener(this);
	brightness->SetVisible(false);
	brightness->Focusable(true);
	vsync = App->gui->CreateButton(iPoint(X_pos + offset, 530), &std::string(conf.child("vsync").attribute("value").as_string("VSYNC")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	vsync->SetFont(App->font->Sherwood20);
	((Gui*)vsync)->SetListener(this);
	vsync->SetVisible(false);
	vsync->Focusable(true);
	vsync_check = App->gui->CreateCheck(iPoint(X_pos + 275, 559), &idle_check_rect, &pressed_check_rect);
	((Gui*)vsync_check)->SetListener(this);
	vsync_check->SetVisible(false);
	vsync_check->ChangeState();
	back = App->gui->CreateButton(iPoint(920, 600), &std::string(conf.child("back").attribute("value").as_string("Back")), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	back->SetFont(App->font->Sherwood20);
	((Gui*)back)->SetListener(this);
	back->SetVisible(false);
	back->Focusable(true);

	buttons.push_back(scale);
	buttons.push_back(fullscreen);
	buttons.push_back(brightness);
	buttons.push_back(vsync);
	buttons.push_back(back);

	return true;
};

bool S_OptionsVideo::Start()
{
	VideoLabel->SetVisible(true);
	scale->SetVisible(true);
	fullscreen->SetVisible(true);
	fullscreen_check->SetVisible(true);
	brightness->SetVisible(true);
	vsync->SetVisible(true);
	vsync_check->SetVisible(true);
	back->SetVisible(true);

	App->gui->SetFocus(buttons.front());

	return true;
}

bool S_OptionsVideo::Update()
{
	MenuInput(&buttons);
	return true;
}

bool S_OptionsVideo::Clean()
{
	VideoLabel->SetVisible(false);
	scale->SetVisible(false);
	fullscreen->SetVisible(false);
	fullscreen_check->SetVisible(false);
	brightness->SetVisible(false);
	vsync->SetVisible(false);
	vsync_check->SetVisible(false);
	back->SetVisible(false);
	return true;
}

void S_OptionsVideo::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)fullscreen) && (event == GuiEvent::mouse_lclk_down))
	{
		fullscreen_check->ChangeState();
		if(fullscreen_check->Checked())
			SDL_SetWindowFullscreen(App->win->window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(App->win->window, 0);
	}
	if ((ui == (Gui*)vsync) && (event == GuiEvent::mouse_lclk_down))
	{
		vsync_check->ChangeState();
		if (vsync_check->Checked())
			SDL_GL_SetSwapInterval(true);
		else
			SDL_GL_SetSwapInterval(false);
	}
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->Show(Scene_ID::options);
	}
}