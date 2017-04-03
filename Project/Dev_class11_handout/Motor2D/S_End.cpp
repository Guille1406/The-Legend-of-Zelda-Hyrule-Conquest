#include "S_End.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"

bool S_End::Start()
{
	LOG("End Open");
	
	finale_texture = App->tex->Load("textures/End.png");
	
	return false;
}

bool S_End::Update() {

	
	
	return true;
}
bool S_End::PostUpdate()
{
	App->win->scale = 1;
	SDL_Rect temp = { 0,0,1000,1000 };
	App->render->Blit(finale_texture, -App->render->camera.x / App->win->scale, -App->render->camera.y / App->win->scale);
	return true;
}
bool S_End::Clean()
{
	

	return false;
}
