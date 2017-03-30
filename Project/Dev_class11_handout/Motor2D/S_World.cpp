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
#include "j1Camera.h"
#include "j1HUD.h"
#include "j1Enemy.h"

bool S_World::Start()
{
	App->camera->Enable();
	App->player->Enable();
	App->hud->Enable();
	if (App->map->Load("tutorial map test.tmx") == true)

	{
		int w, h = 0;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		for (int i = 0; i < App->object->V_Objects->size(); i++) {
			if (App->object->V_Objects[0][i]->collider_tiles.size() > 0) {
				App->object->CreateColliders(*App->object->V_Objects[0][i]);
			}
		}

		int w_two, h_two = 0;
		uchar* data_two = NULL;
		if (App->map->CreateEnemyMap(w_two, h_two, &data_two)) {
			int w_three = 0;
			int h_three = 0;
			uchar* data_three = NULL;
			if (App->map->CreateEnemyPathMap(w_three, h_three, &data_three)) {
				App->enemy->Enable();
			}
		}
			RELEASE_ARRAY(data);
			//App->map->CreateLogicMap();
	}
	


	App->render->camera.x = 0;
	App->render->camera.y = 0;


	App->player->Link->pos = { 660,1100 };
	App->player->Zelda->pos = { 620,1100 };

	
	LOG("World Open");
	return false;
}

bool S_World::Update()
{


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
