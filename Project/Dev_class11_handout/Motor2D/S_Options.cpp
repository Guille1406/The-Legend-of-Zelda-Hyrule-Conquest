#include "S_Options.h"
#include "j1Player.h"
#include "Gui.h"

S_Options::S_Options()
{
}

S_Options::~S_Options()
{
}

bool S_Options::Start()
{
	SDL_Rect idle_button_rect = { 410,165,231,73 };
	SDL_Rect hover_button_rect = { -1,109,231,73 };
	SDL_Rect pressed_button_rect = { 641,165,231,73 };
	OptionsLabel = App->gui->CreateLabel(iPoint(500, 200), &std::string("Options Menu"), false);
	((Gui*)OptionsLabel)->SetListener(this);
	controls = App->gui->CreateButton(iPoint(1000, 370), &std::string("Controls Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)controls)->SetListener(this);
	video = App->gui->CreateButton(iPoint(1000, 450), &std::string("Video Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)video)->SetListener(this);
	audio = App->gui->CreateButton(iPoint(1000, 530), &std::string("Audio Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)audio)->SetListener(this);
	gameplay = App->gui->CreateButton(iPoint(1000, 610), &std::string("Gamplay Settings"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)gameplay)->SetListener(this);
	back = App->gui->CreateButton(iPoint(500, 610), &std::string("Back"), ButtonType::idle_hover_pressed, &idle_button_rect, &hover_button_rect, &pressed_button_rect, false);
	((Gui*)back)->SetListener(this);

	return true;
}

bool S_Options::Update()
{
	return true;
}

bool S_Options::Clean()
{
	return true;
}

void S_Options::OnGui(Gui* ui, GuiEvent event)
{
	if ((ui == (Gui*)back) && (event == GuiEvent::mouse_lclk_down))
	{
		App->scene->ChangeScene(Scene_ID::mainmenu);
	}
}