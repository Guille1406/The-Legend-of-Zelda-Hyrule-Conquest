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
	this->array_pos= App->enemy->CalculatePath(this);
	this->pix_world_pos.x= this->array_pos.x*App->map->data.tile_width;
	this->pix_world_pos.y = this->array_pos.y*App->map->data.tile_height;
}



