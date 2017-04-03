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
#include"j1Audio.h"

bool S_World::Start()
{
	
	App->camera->Enable();
	
	App->hud->Enable();
	App->collision->Enable();
	App->map->Enable();
	App->player->Enable();
		App->object->Enable();
	LOG("IM FUCKING STARTING!!");
	if (App->map->Load("tutorial map test.tmx") == true)

	{
		int w, h = 0;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h);

		for (int i = 0; i < App->object->V_Objects.size(); i++) {
			if (App->object->V_Objects[i]->collider_tiles.size() > 0) {
				App->object->CreateColliders(*App->object->V_Objects[i]);
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
	
	

	App->audio->PlayMusic("audio/music/Sewers_Song.ogg", 1);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	App->player->Link->pos = { 660,1400 };
	App->player->Zelda->pos = { 620,1400 };
	App->player->Link->logic_height = 1;
	App->player->Zelda->logic_height = 1;
	
	LOG("World Open");
	return false;
}

bool S_World::Update()
{
	App->map->Draw();
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
		App->player->loop_game_menu = true;
	}
	
	

	return false;
}
bool S_World::PostUpdate()
{

	if (App->player->loop_game_menu == true || App->player->half_hearts_test_purpose <= 0) {
		App->player->Disable();
		App->enemy->Disable();

		
		App->scene->ChangeScene(Send);

		App->map->Disable();
		App->collision->Disable();
		App->hud->Disable();
		App->scene->ChangeScene(mainmenu);

	}
	return true;

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
