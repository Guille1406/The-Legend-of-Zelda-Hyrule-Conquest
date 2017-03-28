#include "Green_Enemy.h"
#include"j1Enemy.h"
#include"j1Map.h"
Green_Enemy::Green_Enemy():Enemy(enemyType::green_enemy)
{
}
Green_Enemy::Green_Enemy(const Green_Enemy& g_enemy) :Enemy(enemyType::green_enemy)
{
	this->collider = g_enemy.collider;
	this->logic_height = g_enemy.logic_height;
}

Green_Enemy::~Green_Enemy()
{
}

void Green_Enemy::Action()
{
		

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

	if ((actual_tile.x / 16) == array_pos.x && (actual_tile.y / 16) == array_pos.y) {
		passedtile = true;
	}
	else {
		passedtile = false;
	}

	

}



