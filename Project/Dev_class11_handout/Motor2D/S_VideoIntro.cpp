#include "S_QuitGame.h"
#include "j1Player.h"
#include "j1Window.h"
#include "S_VideoIntro.h"
#include "Video.h"
#include "j1Audio.h"

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
	SDL_Rect r = { 0,0,640,360 };
	App->videoplayer->PlayVideo("video.ogv", r);
	return true;
}

bool S_VideoIntro::Update()
{
	//if(!App->videoplayer->active) //Change scene
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {

	
		App->scene->ChangeScene(Scene_ID::mainmenu);
		App->audio->CleanUp();
		App->audio->Awake(App->config);

	
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