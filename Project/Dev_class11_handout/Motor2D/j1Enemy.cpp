#include "j1Enemy.h"
#include"Green_Enemy.h"
#include"j1Collision.h"
#include"j1Map.h"
#include"j1Textures.h"
bool j1Enemy::Awake(pugi::xml_node &)
{

	

	return true;
}
bool j1Enemy::Start()
{
	green_soldier_tex = App->tex->Load("sprites/green_soldier.png.png");

	for (int i = 0; i < App->map->V_Enemies.size(); i++) {
		for (int y = 0; y < App->map->data.height; ++y) {
			for (int x = 0; x < App->map->data.width; ++x) {
				if (App->map->V_Enemies[i]->Get(x, y) != 0) {
					//SDL_Rect enemy_rect = { 0,0,44,60 };
					//App->render->Blit(green_soldier_tex, x*App->map->data.tile_width, y*App->map->data.tile_height, &enemy_rect);
					Create_Enemy(App->map->V_Enemies[i]->Get(x, y), iPoint(x*App->map->data.tile_width, y*App->map->data.tile_height));

				}
			}
		}
	}

	return true;
}

bool j1Enemy::PreUpdate()
{
	return true;
}

bool j1Enemy::Update(float)
{
	SDL_Rect rect = { 0,0,44,60 };
	for (int i = 0; i < V_MyEnemies.size(); i++) {
		App->render->Blit(green_soldier_tex, V_MyEnemies[i]->pos.x, V_MyEnemies[i]->pos.y, &rect);
	}


	return true;
}

bool j1Enemy::PostUpdate()
{

	return true;
}

bool j1Enemy::CleanUp()
{
	return true;
}

Enemy* j1Enemy::Create_Enemy(uint id_enemy, iPoint Pos)
{
	Enemy* ret = nullptr;
	
	switch (id_enemy) {
	case enemyType::green_enemy:
		ret = new Green_Enemy();
		break;




	}

		//This will not be usefull when the enemies will be readed from xml
		ret->pos = Pos;
		SDL_Rect rect = { Pos.x,Pos.y+32,32,32 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, App->enemy);
		ret->logic_height = 1;
		
		V_MyEnemies.push_back(ret);


	return ret;
}
