#include "Enemy_Test_Scene.h"
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

bool S_Enemy_Test_Scene::Start()
{
	scene_str = "Castle Sewers";

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


	if (App->map->Load("Enemy_Map.tmx") == true)

	{
		int w, h = 0;
		uchar* data = nullptr;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h);

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

	App->audio->PlayMusic("audio/music/Sewers_Song.ogg", 0);
	App->audio->VolumeMusic(100);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Link->pos = { 660,1200 };
	App->player->Zelda->pos = { 620,1200 };
	App->player->Link->logic_height = 0;
	App->player->Zelda->logic_height = 0;
	App->player->half_hearts_test_purpose = App->player->hearts_containers_test_purpose * 2;
	LOG("World Open");
	return false;
	return true;
}

bool S_Enemy_Test_Scene::Update()
{
	if (!App->player->paused)
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
			App->player->loop_game_menu = true;
	return true;
}

bool S_Enemy_Test_Scene::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->scene->ChangeScene(Scene_ID::tempbossroom);
	}
	if (App->player->loop_game_menu == true || App->player->half_hearts_test_purpose <= 0) {

		App->scene->ChangeScene(Scene_ID::Send);
		App->startmenuback->Freeze(false);
		App->player->loop_game_menu = false;
		App->player->half_hearts_test_purpose = App->player->hearts_containers_test_purpose * 2;
	}
	return true;
}

bool S_Enemy_Test_Scene::Clean()
{

	App->player->Disable();
	App->enemy->Disable();
	App->map->Disable();
	App->collision->Disable();
	App->hud->Disable();
	App->object->Disable();

	((S_InGameMenu*)App->scene->InGameMenuScene())->active = false;

	return true;
}
