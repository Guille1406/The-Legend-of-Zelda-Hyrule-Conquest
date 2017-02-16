#include "S_Map.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"

bool S_Map::Start()
{
	LOG("Map Open");
	test = new char[20];
	map = App->tex->Load("textures/map.png");
	App->render->camera.x = -400;
	App->render->camera.y = -400;
	return false;
}

bool S_Map::Update() {
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		App->scene->Hide();
		App->render->camera.x = -2500;
		App->render->camera.y = -3400;
	}
	App->render->Blit(map, 0, 0);

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 5;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 5;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 5;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 5;

	
	return true;
}

bool S_Map::Clean()
{
	delete test;
	LOG("Map Test Deleted");
	
	App->tex->UnLoad(map);
	return false;
}
