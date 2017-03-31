#include "Green_Enemy.h"
#include"j1Enemy.h"
#include<math.h>
#include"j1Map.h"
#include"j1Pathfinding.h"
#include"j1Player.h"
Green_Enemy::Green_Enemy():Enemy(enemyType::green_enemy)
{
	this->sprites_vector = App->enemy->enemy_perf->sprites_vector;
	this->character_texture = App->enemy->enemy_perf->character_texture;
	this->ChangeAnimation(1);
}
Green_Enemy::Green_Enemy(const Green_Enemy& g_enemy) :Enemy(enemyType::green_enemy)
{
	this->collider = g_enemy.collider;
	this->logic_height = g_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_perf->sprites_vector;

}

Green_Enemy::~Green_Enemy()
{
}

void Green_Enemy::Action()
{
		
	if (player_in_range == nullptr) {
		iPoint actual_tile = pix_world_pos;
		if (passedtile == true) {
			temp_point = array_pos;
			array_pos = App->enemy->CalculatePath(this);
			if (array_pos == temp_point) {
				Path_Enemy.clear();
			}

		}

		int x = ((array_pos.x) - temp_point.x);


		int y = ((array_pos.y) - temp_point.y);


		pix_world_pos.x += x;
		pix_world_pos.y += y;

		if (x == 1) {
			Enemy_Orientation = OrientationEnemy::right_enemy;
		}
		else if (x == -1) {
			Enemy_Orientation = OrientationEnemy::left_enemy;
		}
		else if (y == 1) {
			Enemy_Orientation = OrientationEnemy::down_enemy;
		}
		else if (y == -1) {
			Enemy_Orientation = OrientationEnemy::up_enemy;
		}


		if ((actual_tile.x / 16) == array_pos.x && (actual_tile.y / 16) == array_pos.y) {
			passedtile = true;
		}
		else {
			passedtile = false;
		}
	}
	else {
		App->pathfinding->SimpleAstar(array_pos, player_in_range->tilepos);

	}
}

void Green_Enemy::Rang_Player()
{

	iPoint dist;
	dist.x = App->player->Link->pos.x - pix_world_pos.x;
	dist.y = App->player->Link->pos.y - pix_world_pos.y;
		if (sqrt((dist.x*dist.x) + (dist.y*dist.y)) < RANG) {
			player_in_range = App->player->Link;
			App->pathfinding->Move(this, player_in_range);
		}
		else {
			player_in_range = nullptr;

		}
		/*
		dist.x = App->player->Zelda->pos.x - pix_world_pos.x;
		dist.y = App->player->Zelda->pos.y - pix_world_pos.y;
		if (sqrt((dist.x*dist.x) + (dist.y*dist.y)) < RANG && player_in_range==nullptr) {
			player_in_range = App->player->Zelda;
		}*/

}


