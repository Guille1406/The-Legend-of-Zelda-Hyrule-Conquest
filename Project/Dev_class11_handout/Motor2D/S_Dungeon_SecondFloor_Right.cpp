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
#include"j1GameStartMenuBack.h"
#include "S_InGameMenu.h"
#include "S_Dungeon_SecondFloor_Right.h"
#include "Video.h"
#include "O_DoubleButton.h"

bool S_DungeonSecondFloorRight::Start()
{
	scene_str = "Van Ruhda Battle Quest";

	App->camera->Enable();
	App->hud->Enable();
	App->collision->Enable();
	App->map->Enable();
	App->player->Enable();
	App->object->Enable();




	//PAUSE FALSE
	App->player->paused = false;
	App->enemy->paused = false;
	App->collision->paused = false;
	App->pathfinding->paused = false;


	if (App->map->Load("Dungeon SecondLevel Right.tmx") == true)

	{
		int w, h = 0;
		uchar* data = nullptr;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h);

		for (uint i = 0; i < App->object->V_Objects.size(); i++) {
			if (App->object->V_Objects[i]->collider_tiles.size() > 0) {
				App->object->CreateColliders(*App->object->V_Objects[i]);
			}
		}

		int w_two, h_two = 0;
		uchar* data_two = nullptr;
		if (App->map->CreateEnemyMap(w_two, h_two, &data_two)) {
			int w_three = 0;
			int h_three = 0;
			uchar* data_three = nullptr;
			if (App->map->CreateEnemyPathMap(w_three, h_three, &data_three)) {
				App->enemy->Enable();
			}
		}
		RELEASE_ARRAY(data);
		//App->map->CreateLogicMap();
	}
	for (uint i = 0; i < App->object->V_Objects.size(); i++) {
		if (App->object->V_Objects[i]->type == objectType::double_button) {
			DoubleButton* temp = (DoubleButton*)App->object->V_Objects[i];
			temp->idle_button = rect_double_red_button_idle;
			temp->pressed_button = rect_double_red_button_one;
			temp->double_pressed_button = rect_double_red_button_pressed;
		}
	}

	App->audio->PlayMusic("audio/music/Dungeon.ogg", 0);
	App->audio->VolumeMusic(100);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//App->player->Link->pos = { 660,1200 };
	//App->player->Zelda->pos = { 620,1200 };

	
	LOG("World Open");
	return false;
}

bool S_DungeonSecondFloorRight::Update()
{
	if (App->scene->puzzle_video_finished && App->videoplayer->video_finished) {

		App->scene->puzzle_video_finished = false;
		App->audio->CleanUp();
		App->audio->Awake(App->config);
		App->audio->Start();
		App->enemy->paused = false;
	}

	if (!App->player->paused)

	return false;
}

bool S_DungeonSecondFloorRight::PostUpdate()
{
	




	return true;


}

bool S_DungeonSecondFloorRight::Clean()
{

	LOG("World Test Deleted");

	App->player->Disable();
	App->enemy->Disable();
	App->map->Disable();
	App->collision->Disable();
	App->hud->Disable();
	App->object->Disable();

	//std::list <TileSet*>::iterator temp = App->map->data.tilesets.begin();

	/*p2List_item<TileSet*>* temp = App->map->data.tilesets.start;
	while (temp != NULL) {
	App->tex->UnLoad(temp->data->texture);
	temp = temp->next;
	}*/

	//This must be revised
	((S_InGameMenu*)App->scene->InGameMenuScene())->active = false;

	return false;
}
