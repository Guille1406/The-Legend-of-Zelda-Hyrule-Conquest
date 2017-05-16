#include "S_Temporal_Boss_Room.h"
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
#include"j1GameStartMenuBack.h"
#include "S_InGameMenu.h"
#include "O_ElectricBall.h"
#include"Video.h"

bool S_TempBossRoom::Start()
{
	scene_str = "HYRULE CASTLE";

	App->camera->Enable();
	App->hud->Enable();
	App->collision->Enable();
	App->map->Enable();
	App->player->Enable();
	App->object->Enable();
	App->enemy->Enable();

	App->enemy->Final_Boss = new Boss();
	App->enemy->Final_Boss->im_active = true;
	//PAUSE FALSE
	App->player->paused = true;
	App->enemy->paused = false;
	App->collision->paused = false;
	App->pathfinding->paused = false;
	SDL_Rect r = { 0,0,1280,720 };
	App->videoplayer->PlayVideo("placeholder.ogv", r);

	if (App->map->Load("final_boss_map_advanced.tmx") == true)

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

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//App->player->Link->pos = { 660,1400 };
	//App->player->Zelda->pos = { 620,1400 };
	App->player->Link->logic_height = 0;
	App->player->Zelda->logic_height = 0;
	
	LOG("World Open");
	App->cutscenemanager->StartCutscene(3);
	return false;
}

bool S_TempBossRoom::Update()
{
	if (App->videoplayer->video_finished && done_video_boss == false)
	{
		App->audio->CleanUp();
		App->audio->Awake(App->config);
		App->audio->Start();
		App->player->paused = false;
		done_video_boss = true;
		App->audio->PlayMusic("audio/music/Final-boss-theme.ogg", 0);
		App->audio->VolumeMusic(100);
	}

	if (!App->player->paused)
		App->enemy->Final_Boss->UpdateLegs();

	return false;
}

bool S_TempBossRoom::PostUpdate()
{
	if (App->videoplayer->video_finished)
	{
		if (App->player->loop_game_menu == true || App->player->half_hearts_test_purpose <= 0) {

			App->scene->ChangeScene(Scene_ID::Send);
			App->startmenuback->Freeze(false);
			App->player->loop_game_menu = false;
			App->player->half_hearts_test_purpose = App->player->hearts_containers_test_purpose * 2;
		}

		for (int i = 0; i < App->object->V_Objects.size(); i++) {
			if (App->object->V_Objects[i]->type == objectType::electric_ball) {
				ElectricBall* temp = (ElectricBall*)App->object->V_Objects[i];
				if (temp->active_phase == 1 && (App->enemy->Final_Boss->actual_phase == boss_phase_2 || App->enemy->Final_Boss->actual_phase == boss_phase_3))
					temp->active = true;
				if (temp->active_phase == 2 && (App->enemy->Final_Boss->actual_phase == boss_phase_3))
					temp->active = true;
			}
		}
		if (App->enemy->Final_Boss != nullptr) {
			if (App->enemy->Final_Boss->boss_defeated) {
				//Play final video
				//if finished App->scene->ChangeScene(Scene_ID::credits);
				App->scene->ChangeScene(Scene_ID::credits);
			}
		}
	}
	return true;

}

bool S_TempBossRoom::Clean()
{
	if (App->enemy->Final_Boss != NULL) {
		App->enemy->Final_Boss->im_active = false;
		delete App->enemy->Final_Boss;
		App->enemy->Final_Boss = NULL;
	}
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

bool S_TempBossRoom::Save(pugi::xml_node& node) const
{
	return true;
}

bool S_TempBossRoom::Load(pugi::xml_node& node)
{
	return true;
}