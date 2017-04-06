#include "S_End.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Audio.h"

S_End::S_End()
{
	scene_str = "End";
}

S_End::~S_End()
{

}

bool S_End::Awake(pugi::xml_node& conf)
{
	return true;
}

bool S_End::Start()
{
	LOG("End Open");
	//App->audio->StopMusic(1000.0f);
	App->audio->VolumeMusic(0);
	finale_texture = App->tex->Load("textures/End.png");
	
	loop_timer.Start();
	return false;
}

bool S_End::Update()
{
	SDL_Rect temp = { 0,0,1000,1000 };
	App->render->Blit(finale_texture, -App->render->camera.x, -App->render->camera.y, NULL, 1.0f, 0, INT_MAX, INT_MAX, false, 255);
	if (loop_timer.Read() > 5000)
		App->scene->ChangeScene(Scene_ID::mainmenu);
	return true;
}

bool S_End::Clean()
{
	App->tex->UnLoad(finale_texture);
	return false;
}
