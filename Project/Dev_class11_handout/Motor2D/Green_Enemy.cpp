#include "Green_Enemy.h"
#include"j1Enemy.h"
#include<math.h>
#include"j1Map.h"
#include"j1Pathfinding.h"
#include"j1Player.h"
#include"j1Audio.h"
Green_Enemy::Green_Enemy():Enemy(enemyType::green_enemy)
{
	this->sprites_vector = App->enemy->enemy_green_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_green_perf->entity_texture;
	this->ChangeAnimation(1);
}
Green_Enemy::Green_Enemy(const Green_Enemy& g_enemy) :Enemy(enemyType::green_enemy)
{
	this->collider = g_enemy.collider;
	this->logic_height = g_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_green_perf->sprites_vector;

}

Green_Enemy::~Green_Enemy()
{
}

void Green_Enemy::Action()
{
	tile_pos.x = pos.x / 16;
	tile_pos.y = pos.y / 16;
	if (player_in_range == nullptr) {
		iPoint actual_tile = pos;
		if (passedtile == true) {
			temp_point = array_pos;
			array_pos = App->enemy->CalculatePath(this);
			if (array_pos == temp_point) {
				Path_Enemy.clear();
			}

		}

		int x = ((array_pos.x) - temp_point.x);


		int y = ((array_pos.y) - temp_point.y);


		pos.x += x;
		pos.y += y;

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
		

	}
}
