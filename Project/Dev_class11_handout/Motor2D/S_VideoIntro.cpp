#include "S_QuitGame.h"
#include "j1Player.h"
#include "j1Window.h"
#include "S_VideoIntro.h"

S_VideoIntro::S_VideoIntro()
{
	scene_str = "VideoIntro";
}

S_VideoIntro::~S_VideoIntro()
{
}

bool S_VideoIntro::Awake(pugi::xml_node& conf)
{
	return true;
}

bool S_VideoIntro::Start()
{
	return true;
}

bool S_VideoIntro::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		App->scene->ChangeScene(Scene_ID::mainmenu);
	}
	//MenuInput(&buttons);
	return true;
}

bool S_VideoIntro::Clean()
{
	return true;
}

void S_VideoIntro::OnGui(Gui* ui, GuiEvent event)
{

}

bool S_VideoIntro::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_VideoIntro::Load(pugi::xml_node& node)
{
	return true;
}