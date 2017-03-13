#include "S_World.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Scene.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Pathfinding.h"
#include "j1App.h"
#include "j1Player.h"

bool S_World::Start()
{

	App->player->Enable();
	if (App->map->Load("zelda_map_2.tmx") == true)

	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);
	}
	App->render->camera.x = 0;
	App->render->camera.y = 0;


	App->player->Link->pos = { 0,0 };
	App->player->Zelda->pos = { 16,16 };

	
	LOG("World Open");
	return false;
}

bool S_World::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		App->scene->ChangeScene(dungeon);
	}

	/*
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 5;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 5;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 5;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 5;
*/

	App->map->Draw();


	return false;
}

bool S_World::Clean()
{
	
	LOG("World Test Deleted");

	//std::list <TileSet*>::iterator temp = App->map->data.tilesets.begin();
	for (std::list <TileSet*>::iterator temp = App->map->data.tilesets.begin(); temp != App->map->data.tilesets.cend(); ++temp) {
		App->tex->UnLoad((*temp)->texture);
	}

	/*p2List_item<TileSet*>* temp = App->map->data.tilesets.start;
	while (temp != NULL) {
		App->tex->UnLoad(temp->data->texture);
		temp = temp->next;
	}*/

	App->map->CleanUp();
	
	return false;
}
