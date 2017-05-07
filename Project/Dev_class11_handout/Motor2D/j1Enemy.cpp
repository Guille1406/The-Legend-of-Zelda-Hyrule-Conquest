#include "j1Enemy.h"
#include"ChampionSoldier_Enemy.h"
#include"Green_Enemy.h"
#include"j1Collision.h"
#include"j1Map.h"
#include"j1Textures.h"
#include"j1Player.h"
#include"j1Pathfinding.h"
#include"j1Audio.h"
#include"HyruleBombSoldier_Enemy.h"
#include"Statue_Enemy.h"
#include"Rope_Enemy.h"
#include"SkullRopes_Enemy.h"
#include"Rat_Enemy.h"
#include"Bat_Enemy.h"
#include <time.h> 
#include "Brofiler/Brofiler.h"

bool j1Enemy::Awake(pugi::xml_node &)
{
	Frame smoke_frame;
	smoke_frame.pivot = { 0,0 };
	smoke_frame.rect = { 187,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 282,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 375,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 470,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 563,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 658,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 751,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 845,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	smoke_frame.rect = { 940,501,94,81 };
	Enemies_Appear.PushBack(smoke_frame);
	Enemies_Appear.speed = 0.0f;
	
	return true;
}
bool j1Enemy::Start()
{
	one_time_appear = 0;
	appear_enemies = false;
	enemy_green_perf = new Enemy();
	enemy_green_perf->LoadAnimation("sprites/Enemy_green.xml");
	enemy_hyrulebomb_perf = new Enemy();
	enemy_hyrulebomb_perf->LoadAnimation("sprites/Enemy_redsoldier.xml");
	enemy_shield_perf = new Enemy();
	enemy_shield_perf->LoadAnimation("sprites/Enemy_shield.xml");
	enemy_statue_perf = new Enemy();
	enemy_statue_perf->LoadAnimation("sprites/Enemy_armos.xml");
	enemy_rope_perf = new Enemy();
	enemy_rope_perf->LoadAnimation("sprites/Enemy_rope.xml");
	enemy_skullrope_perf = new Enemy();
	enemy_skullrope_perf->LoadAnimation("sprites/Enemy_skullrope.xml");
	enemy_rat_perf = new Enemy();
	enemy_rat_perf->LoadAnimation("sprites/Enemy_rat.xml");
	enemy_bat_perf = new Enemy();
	enemy_bat_perf->LoadAnimation("sprites/Enemy_bat.xml");


	for (int i = 0; i < App->map->V_Enemies.size(); i++) {
		for (int y = 0; y < App->map->data.height; ++y) {
			for (int x = 0; x < App->map->data.width; ++x) {
				if (App->map->V_Enemies[i]->Get(x, y) != 0) {
					Create_Enemy(App->map->V_Enemies[i]->Get(x, y), iPoint(x, y), i);

				}
			}
		}
	}


	return true;
}

bool j1Enemy::PreUpdate()
{
	BROFILER_CATEGORY("j1Enemy PreUpdate", Profiler::Color::LightYellow);
	if (!paused) {
		for (int i = 0; i < V_MyEnemies.size(); i++) {
			if (V_MyEnemies[i]->tokill == true) {
				if (V_MyEnemies[i]->collider->type == collider_enemy)
					V_MyEnemies[i]->DropObject();
					V_MyEnemies[i]->collider->to_delete = true;
				if(V_MyEnemies[i]->shield_test!=nullptr){
				if(V_MyEnemies[i]->shield_test->type == collider_enemy_sword)
				V_MyEnemies[i]->shield_test->to_delete = true;
				}

				std::vector<Enemy*>::iterator it = std::find(App->enemy->V_MyEnemies.begin(), App->enemy->V_MyEnemies.end(), V_MyEnemies[i]);
				V_MyEnemies.erase(it);


			}
		}
		if (appear_enemies && one_time_appear < 1) {
			//smoke animation
			
			Create_Enemy(enemyType::green_enemy, iPoint(75, 41),0);
			Create_Enemy(enemyType::green_enemy, iPoint(63, 56),0);
			one_time_appear++;
			appear_enemies = false;
		}
	}
	return true;
}

bool j1Enemy::Update(float dt)
{
	BROFILER_CATEGORY("j1Enemy Update", Profiler::Color::LightYellow);
	for (int i = 0; i < V_MyEnemies.size(); i++)
		if (!paused) {

			V_MyEnemies[i]->UpdateState();
			V_MyEnemies[i]->Rang_Player();
			V_MyEnemies[i]->collider->rect.x = V_MyEnemies[i]->pos.x;
			V_MyEnemies[i]->collider->rect.y = V_MyEnemies[i]->pos.y;
			Update_Sword_Collision(V_MyEnemies[i]);
			V_MyEnemies[i]->Action();
		}

	return true;
}

bool j1Enemy::PostUpdate()
{

	return true;
}

bool j1Enemy::CleanUp()
{
	
	for (int i = 0; i < V_MyEnemies.size(); i++)
	{
		App->tex->UnLoad(V_MyEnemies[i]->entity_texture);
	}
	for (std::vector<Animation*>::iterator item = Green_Enemy_Animation.begin(); item != Green_Enemy_Animation.cend(); ++item)
		RELEASE(*item);
	Green_Enemy_Animation.clear();
	for (std::vector<Enemy*>::iterator item = V_MyEnemies.begin(); item != V_MyEnemies.cend(); ++item)
		RELEASE(*item);

	V_MyEnemies.clear();
	appear_enemies = false;
	one_time_appear = 0;
	return true;
}


void j1Enemy::Draw(int height, int y_pos)
{
	for (int i = 0; i < V_MyEnemies.size(); i++) {
		if(V_MyEnemies[i]->logic_height == height && V_MyEnemies[i]->tile_pos.y == y_pos)
		App->render->Blit(V_MyEnemies[i]->entity_texture, V_MyEnemies[i]->pos.x - V_MyEnemies[i]->actual_animation.GetCurrentFrame().pivot.x, V_MyEnemies[i]->pos.y - V_MyEnemies[i]->actual_animation.GetCurrentFrame().pivot.y, &V_MyEnemies[i]->actual_animation.GetCurrentFrame().rect);
	}
}


Enemy* j1Enemy::Create_Enemy(uint id_enemy, iPoint pos_array_enemy, int height)
{
	Enemy* ret = nullptr;
	SDL_Rect rect_test = { 0,0,0,0 };
	SDL_Rect rect = { 0,0,0,0 };
	switch (id_enemy) {
	case enemyType::green_enemy:
		ret = new Green_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 2;
		//This will not be usefull when the enemies will be readed from xml
		rect_test = { ret->array_pos.x,ret->array_pos.y,20,10 };
		ret->shield_test = App->collision->AddCollider(rect_test, COLLIDER_TYPE::collider_enemy_sword, ret, (j1Module*)App->enemy);
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;


		rect = { ret->pos.x, ret->pos.y + 32,26,30 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret,(j1Module*) App->enemy);
		

		ret->item.up_ofset_item_enemy = { 0, 0 };//This may change

		ret->item.down_ofset_item_enemy = { 20, 10 };
		ret->item.right_ofset_item_enemy = { 16, 20 };
		ret->item.left_ofset_item_enemy = { -5, 20 };
		ret->item.Shield_dimensions = { 20,10 };
		
		
		//how to know if a enemy is in level one or two
		ret->logic_height = height;
		break;

	case enemyType::championsoldier_enemy:
		ret = new Championsoldier_Enemy();
		//i don't have the sprite of enemy
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 2;
		
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;

		rect = { ret->pos.x, ret->pos.y + 32,30,35 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);

		//how to know if a enemy is in level one or two
		ret->logic_height = height;
		break;

	case enemyType::statue_enemy:
		ret = new Statue_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 6;
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;


		rect = { ret->pos.x, ret->pos.y + 32,30,35 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);
		//how to know if a enemy is in level one or two
		ret->max_heigh_jump.y = ret->pos.y - 50;
		ret->logic_height = height;
		break;

	case enemyType::rope_enemy:
		ret = new Rope_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 6;
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;


		rect = { ret->pos.x, ret->pos.y + 32,30,35 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);
		//how to know if a enemy is in level one or two
		ret->logic_height = height;
		break;

	case enemyType::rat_enemy:
		ret = new Rat_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 6;
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;


		rect = { ret->pos.x, ret->pos.y + 32,30,35 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);
		//how to know if a enemy is in level one or two
		ret->logic_height = height;
		break;

	case enemyType::skullrope_enemy:
		ret = new SkullRope_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 6;
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;


		rect = { ret->pos.x, ret->pos.y + 32,30,35 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);
		//how to know if a enemy is in level one or two
		ret->logic_height = height;
		break;

	case enemyType::bat_enemy:
		ret = new Bat_Enemy();
		ret->rect = { 0,0,44,60 };
		ret->array_pos = pos_array_enemy;
		ret->live = 4;
		//Position in world pixel 
		ret->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		ret->pos.y = pos_array_enemy.y*App->map->data.tile_height;


		rect = { ret->pos.x, ret->pos.y + 32,30,35 };
		ret->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);
		//how to know if a enemy is in level one or two
		ret->logic_height = height;
		break;

	case enemyType::hyrulebombsoldier_enemy:

		ret = new HyruleBombSoldier_Enemy();
		HyruleBombSoldier_Enemy* temp = (HyruleBombSoldier_Enemy*)ret;
		//i don't have the sprite of enemy
		temp->rect = { 0,0,44,60 };
		temp->array_pos = pos_array_enemy;
		temp->live = 5;

		//Position in world pixel 
		temp->pos.x = pos_array_enemy.x*App->map->data.tile_width;
		temp->pos.y = pos_array_enemy.y*App->map->data.tile_height;

		temp->bomb_point.x = temp->pos.x;
		temp->bomb_point.y = temp->pos.y;

		temp->max_bomb_point.x = temp->pos.x;
		temp->max_bomb_point.y = temp->pos.y-50;
		rect = { ret->pos.x, ret->pos.y + 32,30,35};
		temp->logic_height = height;
		temp->collider = App->collision->AddCollider(rect, COLLIDER_TYPE::collider_enemy, (Entity*)ret, (j1Module*)App->enemy);

		//how to know if a enemy is in level one or two

		ret = temp;
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
	if (enemy->Path_Enemy.size() > 1)
	{
		enemy->Path_Enemy.clear();
	}
	else
	{
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
	int animation = (int)enemy->state * 4 + (int)enemy->Enemy_Orientation;
	enemy->ChangeAnimation(animation);
	if (enemy->type== enemyType::green_enemy) {
		switch (enemy->Enemy_Orientation) {

		case OrientationEnemy::up_enemy:
			enemy->shield_test->rect = { enemy->collider->rect.x + enemy->item.up_ofset_item_enemy.x, enemy->collider->rect.y + enemy->item.up_ofset_item_enemy.y , enemy->item.Shield_dimensions.y, enemy->item.Shield_dimensions.x };
			break;

		case OrientationEnemy::down_enemy:
			enemy->shield_test->rect = { enemy->collider->rect.x + enemy->item.down_ofset_item_enemy.x, enemy->collider->rect.y + enemy->item.down_ofset_item_enemy.y, enemy->item.Shield_dimensions.y, enemy->item.Shield_dimensions.x };
			break;

		case OrientationEnemy::right_enemy:
			enemy->shield_test->rect = { enemy->collider->rect.x + enemy->item.right_ofset_item_enemy.x, enemy->collider->rect.y + enemy->item.right_ofset_item_enemy.y, enemy->item.Shield_dimensions.x, enemy->item.Shield_dimensions.y };
			break;

		case OrientationEnemy::left_enemy:
			//20,10
			enemy->shield_test->rect = { enemy->collider->rect.x + enemy->item.left_ofset_item_enemy.x, enemy->collider->rect.y + enemy->item.left_ofset_item_enemy.y,enemy->item.Shield_dimensions.x, enemy->item.Shield_dimensions.y };
			break;
		}
	}
}

void Enemy::Direction_Push_Election()
{
	//Calls the jump function depending on the player direction
	switch (App->player->Link->character_direction) {
	case direction::up:
		Enemy_Hurt_Displacement(pos.y, false);
		break;
	case direction::down:
		Enemy_Hurt_Displacement(pos.y, true);
		break;
	case direction::left:
		Enemy_Hurt_Displacement(pos.x, false);
		break;
	case direction::right:
		Enemy_Hurt_Displacement(pos.x, true);
		break;
	}
}

void Enemy::Direction_Push_Election_ChSoldier()
{
	//Calls the jump function depending on the player direction
	switch (App->player->Link->character_direction) {
	case direction::up:
		Enemy_Hurt_Displacement(pos.y, false);
		break;
	case direction::down:
		Enemy_Hurt_Displacement(pos.y, true);
		break;
	case direction::left:
		Enemy_Hurt_Displacement(pos.x, false);
		break;
	case direction::right:
		Enemy_Hurt_Displacement(pos.x, true);
		break;
	}
}

void j1Enemy::OnCollision(Collider * collider1, Collider * collider2)
{
	Character* character = nullptr;
	if (collider1->type == collider_link || collider2->type == collider_link)
		character = App->player->Link;
	else if (collider1->type == collider_zelda || collider2->type == collider_zelda)
		character = App->player->Zelda;
	else if (collider1->type == front_zelda || collider2->type == front_zelda)
		character = App->player->Zelda;
	else if (collider1->type == front_link || collider2->type == front_link)
		character = App->player->Link;

	if (collider1->type == COLLIDER_TYPE::collider_enemy_sword && collider2->type == COLLIDER_TYPE::collider_link) {
		Enemy* n_enemy = (Enemy*)collider1->parent;
		if (App->player->Link->is_rolling == false) {
			//if (Link->roll_timer.Read() > 1500) {
			if (App->player->Link->collision_by_enemy_timmer.Read() > 1500) {
				App->player->Link->collision_by_enemy_timmer.Start();
				App->player->Link->actual_event = player_event::push_backwards;
				App->player->Link->doing_script = true;
				App->player->Link->Direction_Push_Election();
				App->player->half_hearts_test_purpose--;

			}
			//}
		}
	}
	else if (collider1->type == COLLIDER_TYPE::collider_enemy_sword && collider2->type == COLLIDER_TYPE::collider_zelda) {
		Enemy* n_enemy = (Enemy*)collider1->parent;
		if (App->player->Zelda->is_rolling == false) {
			if (App->player->Link->collision_by_enemy_timmer.Read() > 1500) {
				App->player->Link->collision_by_enemy_timmer.Start();
				App->player->Zelda->actual_event = player_event::push_backwards;
				App->player->Zelda->doing_script = true;
				App->player->Zelda->Direction_Push_Election();
				App->player->half_hearts_test_purpose--;
				
			}

		}
	}
}

void j1Enemy::EndCollision(Collider * collider1, Collider * collider2)
{
	
}

void j1Enemy::StartCollision(Collider* collider1, Collider* collider2)
{

	
}

void Enemy::Rang_Player() {
	//this->player_in_range = nullptr;
	iPoint dist;
	dist.x = App->player->Link->pos.x - this->pos.x;
	dist.y = App->player->Link->pos.y - this->pos.y;
	iPoint dist2;
	dist2.x = App->player->Zelda->pos.x - pos.x;
	dist2.y = App->player->Zelda->pos.y - pos.y;
	if (this->type!= enemyType::rat_enemy) {
		if (sqrt((dist.x*dist.x) + (dist.y*dist.y)) < RANG && enemy_doing_script == false) {
			this->player_in_range = App->player->Link;
			//green_enemy_path.clear();
			if (tile_pos != iPoint(0, 0) && player_in_range->GetLogicHeightPlayer() == 0) {
				if (App->pathfinding->SimpleAstar(tile_pos, player_in_range->tilepos) != nullptr) {
					green_enemy_path = *App->pathfinding->SimpleAstar(tile_pos, player_in_range->tilepos);
				}
				if (green_enemy_path.size()) {
					App->pathfinding->Move(this, player_in_range);
				}
			}
		}

		else if (sqrt((dist2.x*dist2.x) + (dist2.y*dist2.y)) < RANG  && enemy_doing_script == false) {
			this->player_in_range = App->player->Zelda;
			//green_enemy_path.clear();
			if (tile_pos != iPoint(0, 0) && player_in_range->GetLogicHeightPlayer() == 0) {
				if (App->pathfinding->SimpleAstar(tile_pos, player_in_range->tilepos) != nullptr) {
					green_enemy_path = *App->pathfinding->SimpleAstar(tile_pos, player_in_range->tilepos);
				}
				if (green_enemy_path.size()) {
					App->pathfinding->Move(this, player_in_range);
				}
			}
		}
		else {
			if (type == enemyType::hyrulebombsoldier_enemy) {
				this->player_in_range = nullptr;
			}
		}
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
				/*if (type == enemyType::hyrulebombsoldier_enemy) {
					HyruleBombSoldier_Enemy* temp_enemy = (HyruleBombSoldier_Enemy*) this;
					if (temp_enemy->bomb->bomb_explosion == false)
						state = EnemyState::throwing_bomb;
					else
						state = EnemyState::doing_path;
				}*/

		}
		else {
			if (type == enemyType::hyrulebombsoldier_enemy) {
				
				state = EnemyState::throwing_bomb;
			}
			else if (type == enemyType::statue_enemy) {
				state = EnemyState::jumping;
			}
			else {
				state = EnemyState::following_player;
			}
		}
	}
	else {
		if (type == enemyType::championsoldier_enemy) {
			Direction_Push_Election_ChSoldier();
		}
		else {
			if (type != enemyType::statue_enemy) {
				Direction_Push_Election();
			}
		}
	}
}

void Enemy::Enemy_Hit_Comprobation(Collider* collider)
{

	switch (type)
	{
	case enemyType::rat_enemy:
	case enemyType::skullrope_enemy:
	case enemyType::rope_enemy:
	case enemyType::green_enemy:
		if (collider->type == COLLIDER_TYPE::collider_link_sword) {
			if (live > 0) {
				if (App->player->Link->link_sword_impact_sword == false) {
					App->player->Link->enemy_col_sword_sword_timer.Start();
					state = EnemyState::push_back_enemy;
					enemy_doing_script = true;
					App->audio->PlayFx(App->enemy->enemy_dies_audio);
					live--;
				}
				else {
					App->player->Link->link_sword_impact_sword = false;
				}
			}
			else {
				App->audio->PlayFx(App->enemy->enemy_dies_audio);
				tokill = true;
			}
		}
		else if (collider->type == COLLIDER_TYPE::collider_arrow) {
			if (live > 0) {
				live--;
			}
			else {
				tokill = true;
			}
		}
		break;
	case enemyType::bat_enemy:

		if (collider->type == COLLIDER_TYPE::collider_arrow) {
			if (live > 0) {
				live--;
			}
			else {
				tokill = true;
			}
		}


		break;

	case enemyType::championsoldier_enemy:
		if (collider->type == COLLIDER_TYPE::collider_link_sword) {
			if (live > 0) {
				if (App->player->Link->link_sword_impact_sword == false && App->player->Link->Compare_Link_Sword_Collision(this) == false) {
					App->player->Link->enemy_col_sword_sword_timer.Start();
					state = EnemyState::push_back_enemy;
					enemy_doing_script = true;
					App->audio->PlayFx(App->enemy->enemy_dies_audio);
					live--;
				}
				else {
					App->player->Link->actual_event = player_event::push_backwards;
					App->player->Link->doing_script = true;
					App->player->Link->Direction_Push_Election();
					App->player->Link->link_sword_impact_sword = false;
				}
			}
			else {
				App->audio->PlayFx(App->enemy->enemy_dies_audio);
				tokill = true;
			}
		}
		else if (collider->type == COLLIDER_TYPE::collider_arrow) {
			bool hit = false;
			Arrow *temp;
			temp = (Arrow*)collider->parent;
				switch (temp->direction) {
				case arrow_direction::arrow_up:
					if (Enemy_Orientation==OrientationEnemy::up_enemy)
						hit = true;
					break;
				case arrow_direction::arrow_down:
					if (Enemy_Orientation == OrientationEnemy::down_enemy)
						hit = true;
					break;
				case arrow_direction::arrow_right:
					if (Enemy_Orientation == OrientationEnemy::right_enemy)
						hit = true;
					break;
				case arrow_direction::arrow_left:
					if (Enemy_Orientation == OrientationEnemy::left_enemy)
						hit = true;
					break;

				}
			if (live > 0 ) {
				if (hit == true) {
					live--;
					hit = false;
				}
			}
			else {
				tokill = true;
			}
		}
		



		break;
	case enemyType::hyrulebombsoldier_enemy:
		if (collider->type == COLLIDER_TYPE::collider_arrow) {
			if (live > 0) {
				live--;
			}
			else {
				tokill = true;
			}
		}
		break;

	case enemyType::statue_enemy:

		if (collider->type == COLLIDER_TYPE::collider_link_sword) {
			if (live > 0) {
				if (App->player->Link->link_sword_impact_sword == false && state!= EnemyState::stunned) {
					App->player->Link->enemy_col_sword_sword_timer.Start();
					state = EnemyState::stunned;
					enemy_doing_script = true;
					script_timer.Start();
					App->audio->PlayFx(App->enemy->enemy_dies_audio);
					live--;
				}
				else {
					App->player->Link->link_sword_impact_sword = false;
				}
			}
			else {
				App->audio->PlayFx(App->enemy->enemy_dies_audio);
				tokill = true;
			}
		}
		else if (collider->type == COLLIDER_TYPE::collider_arrow) {
			if (live > 0 && state != EnemyState::stunned) {
				live--;
			}
			else {
				tokill = true;
			}
		}
		break;
	

	}
}

void Enemy::DropObject() {

	srand(time(NULL));
	int what_drope = 0; 
	what_drope = rand() % 2;
	switch (what_drope) {

	case 0:
		//Drop nothing
		break;
	case 1:
		App->object->CreateHeart(this, this->logic_height);
		break;

	case 2:
		//If we finally add fire arrows
		break;
	}

}

