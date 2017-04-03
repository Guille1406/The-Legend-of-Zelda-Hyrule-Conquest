#include "j1Enemy.h"
#include"Green_Enemy.h"
#include"j1Collision.h"
#include"j1Map.h"
#include"j1Textures.h"
#include"j1Player.h"
bool j1Enemy::Awake(pugi::xml_node &)
{

	
	return true;
}
bool j1Enemy::Start()
{
	enemy_perf = new Enemy();
	enemy_perf->LoadAnimation("sprites/green_enemy.xml");
	
	for (int i = 0; i < App->map->V_Enemies.size(); i++) {
		for (int y = 0; y < App->map->data.height; ++y) {
			for (int x = 0; x < App->map->data.width; ++x) {
				if (App->map->V_Enemies[i]->Get(x, y) != 0) {
					Create_Enemy(App->map->V_Enemies[i]->Get(x, y), iPoint(x, y));

				}
			}
		}
	}


	

	return true;
}

bool j1Enemy::PreUpdate()
{
	if (!paused) {
		for (int i = 0; i < V_MyEnemies.size(); i++) {
			if (V_MyEnemies[i]->tokill == true) {
				V_MyEnemies[i]->collider->to_delete = true;
				V_MyEnemies[i]->shield_test->to_delete = true;
				std::vector<Enemy*>::iterator it = std::find(App->enemy->V_MyEnemies.begin(), App->enemy->V_MyEnemies.end(), V_MyEnemies[i]);
				V_MyEnemies.erase(it);


			}
		}
		if (appear_enemies && one_time_appear < 1) {
			Create_Enemy(enemyType::green_enemy, iPoint(75, 41));
			Create_Enemy(enemyType::green_enemy, iPoint(63, 56));
			one_time_appear++;
			appear_enemies = false;
		}
	}
	return true;
}

bool j1Enemy::Update(float dt)
{

		for (int i = 0; i < V_MyEnemies.size(); i++) {
						
			if (!paused) {
				
				V_MyEnemies[i]->UpdateState();
				V_MyEnemies[i]->Rang_Player();
				V_MyEnemies[i]->collider->rect.x = V_MyEnemies[i]->pix_world_pos.x;
				V_MyEnemies[i]->collider->rect.y = V_MyEnemies[i]->pix_world_pos.y;
				Update_Sword_Collision(V_MyEnemies[i]);
				V_MyEnemies[i]->Action();
			}
		}


	return true;
}

bool j1Enemy::PostUpdate()
{

	return true;
}

bool j1Enemy::CleanUp()
{
	V_MyEnemies.clear();
	return true;
}


void j1Enemy::Draw(int height, int y_pos)
{
	for (int i = 0; i < V_MyEnemies.size(); i++) {
		if(V_MyEnemies[i]->logic_height == height && V_MyEnemies[i]->tile_pos.y == y_pos)
		App->render->Blit(V_MyEnemies[i]->entity_texture, V_MyEnemies[i]->pix_world_pos.x - V_MyEnemies[i]->actual_animation.GetCurrentFrame().pivot.x, V_MyEnemies[i]->pix_world_pos.y - V_MyEnemies[i]->actual_animation.GetCurrentFrame().pivot.y, &V_MyEnemies[i]->actual_animation.GetCurrentFrame().rect);
	}
}


Enemy* j1Enemy::Create_Enemy(uint id_enemy, iPoint pos_array_enemy)
{
	Enemy* ret = nullptr;
	
	switch (id_enemy) {
	case enemyType::green_enemy:
		ret = new Green_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 2;
		//This will not be usefull when the enemies will be readed from xml
		SDL_Rect rect_test = { ret->array_pos.x,ret->array_pos.y,20,10 };
		ret->shield_test = App->collision->AddCollider(rect_test, COLLIDER_TYPE::collider_enemy_sword, ret, this);


		//Position in world pixel 
		ret->pix_world_pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pix_world_pos.y = pos_array_enemy.y*App->map->data.tile_height;

		SDL_Rect rect = { ret->pix_world_pos.x + 16, ret->pix_world_pos.y + 32,16,42 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, App->enemy);
		ret->logic_height = 0;
		break;

	}
	//Position in array
	if (ret != nullptr) {
		V_MyEnemies.push_back(ret);
	}

	return ret;
}

iPoint j1Enemy::CalculatePath(Enemy* enemy)
{
	if (FindInPath(enemy->array_pos, enemy) == false) {
		enemy->Path_Enemy.push_back(enemy->array_pos);
	}
	iPoint cell;
	for (int i = 0; i < App->map->V_PathEnemies.size(); i++) {
		if (enemy->movable == true) {
			cell.create(enemy->array_pos.x, enemy->array_pos.y + 1);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell, enemy) == false) {
				enemy->Path_Enemy.push_back(cell);
				return cell;
			}

			cell.create(enemy->array_pos.x, enemy->array_pos.y - 1);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell, enemy) == false) {
				enemy->Path_Enemy.push_back(cell);
				return cell;
			}

			cell.create(enemy->array_pos.x + 1, enemy->array_pos.y);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell, enemy) == false) {
				enemy->Path_Enemy.push_back(cell);
				return cell;
			}

			cell.create(enemy->array_pos.x - 1, enemy->array_pos.y);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell, enemy) == false) {
				enemy->Path_Enemy.push_back(cell);
				return cell;
			}

		}
	}
	if (enemy->Path_Enemy.size()>1) {
		enemy->Path_Enemy.clear();
	}
	else {
		enemy->movable = false;
	}
	return enemy->array_pos;
}

bool j1Enemy::FindInPath(iPoint pos, Enemy* enemy) {

	for (std::list<iPoint>::iterator item = enemy->Path_Enemy.begin(); item != enemy->Path_Enemy.cend(); ++item) {
		if ((*item) == pos) {
			return true;
		}
	}
	return false;
}

void j1Enemy::Update_Sword_Collision(Enemy* enemy)
{

		int animation = (int)enemy->Enemy_Orientation;
		enemy->ChangeAnimation(animation);

	switch (enemy->Enemy_Orientation) {

	case OrientationEnemy::up_enemy:

		enemy->shield_test->rect = { enemy->collider->rect.x-10, enemy->collider->rect.y + 10 , 10,20 };
		break;

	case OrientationEnemy::down_enemy:
		
		enemy->shield_test->rect = { enemy->collider->rect.x+12, enemy->collider->rect.y + enemy->collider->rect.h -10 , 10,20};

		break;

	case OrientationEnemy::right_enemy:
		enemy->shield_test->rect = { enemy->collider->rect.x + 10, enemy->collider->rect.y + 30 , 20,10 };

		break;

	case OrientationEnemy::left_enemy:
		
		//20,10
		enemy->shield_test->rect = { enemy->collider->rect.x - 18, enemy->collider->rect.y + 30 , 20,10 };

		break;



	}
}


void Enemy::Direction_Push_Election()
{
	//Calls the jump function depending on the player direction
	switch (Enemy_Orientation) {
	case OrientationEnemy::up_enemy:
		Enemy_Hurt_Displacement(pix_world_pos.y, true);
		break;
	case OrientationEnemy::down_enemy:
		Enemy_Hurt_Displacement(pix_world_pos.y, false);
		break;
	case OrientationEnemy::left_enemy:
		Enemy_Hurt_Displacement(pix_world_pos.x, true);
		break;
	case OrientationEnemy::right_enemy:
		Enemy_Hurt_Displacement(pix_world_pos.x, false);
		break;
	}
}


void Enemy::Enemy_Hurt_Displacement(int & pos, bool add)
{

	static int final_pos = 0;
	//same as jump function
	int i = 1;
	if (!add)
		i = -1;

	if (!temp)
		final_pos = pos + (i * PUSH_DISTANCE);
	temp = true;

	//if player have wall in front the roll will stop
	if ((i * pos <  i*final_pos) && GetLogicEnemy(false, tile_pos) == 0) {
		pos = pos + (i * 4);
	}
	else {
		enemy_doing_script = false;
		temp = false;
	}

}

int Enemy::GetLogicEnemy(int minus_height, iPoint pos)
{
	//Takes the id of the two front tiles of each player, depending on the locig height of each player
	std::vector<MapLayer*> vector = App->map->V_Colision;

	iPoint tile_pos = pos;


	int i, j;
	switch (Enemy_Orientation)
	{
	case OrientationEnemy::up_enemy:
		i = vector[logic_height - minus_height]->Get(tile_pos.x, tile_pos.y + 1);
		j = vector[logic_height - minus_height]->Get(tile_pos.x + 1, tile_pos.y + 1);
		break;
	case OrientationEnemy::down_enemy:
		i = vector[logic_height - minus_height]->Get(tile_pos.x, tile_pos.y - 2);
		j = vector[logic_height - minus_height]->Get(tile_pos.x - 1, tile_pos.y - 2);
		break;
	case OrientationEnemy::left_enemy:
		i = vector[logic_height - minus_height]->Get(tile_pos.x + 1, tile_pos.y);
		j = vector[logic_height - minus_height]->Get(tile_pos.x + 1, tile_pos.y - 1);
		break;
	case OrientationEnemy::right_enemy:
		i = vector[logic_height - minus_height]->Get(tile_pos.x - 2, tile_pos.y);
		j = vector[logic_height - minus_height]->Get(tile_pos.x - 2, tile_pos.y - 1);
		break;
	}

	if (i != 0)return i;
	if (j != 0)return j;
	return 0;
}

void Enemy::UpdateState()
{
	if (enemy_doing_script == false) {
		if (player_in_range == nullptr) {
			state = EnemyState::doing_path;
		}
		else {
			state = EnemyState::following_player;
		}
	}
	else {
		Direction_Push_Election();
	}
}





