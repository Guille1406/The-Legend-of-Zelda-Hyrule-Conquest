#include "S_Dungeon.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Textures.h"

bool S_Dungeon::Start()
{
	LOG("Dungeon Open");
	test = new char[20];

	
	return false;
}

bool S_Dungeon::Update() {
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		App->scene->Show(map);
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		App->scene->Show(inventory);
	}
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		App->scene->ChangeScene(world);
	}
	App->map->Draw();

	return true;
}

bool S_Dungeon::Clean()
{
	delete test;
	LOG("Dungeon Test Deleted");

	for (std::list <TileSet*>::iterator temp = App->map->data.tilesets.begin(); temp != App->map->data.tilesets.cend(); ++temp) {
		App->tex->UnLoad((*temp)->texture);
	}

	App->map->CleanUp();
	
	return false;
}
