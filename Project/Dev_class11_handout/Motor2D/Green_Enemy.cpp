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
	if (passedtile==true) {
		array_pos = App->enemy->CalculatePath(this);
	}
	/*iPoint next_tile;
	next_tile.x = array_pos.x*App->map->data.tile_width;
	next_tile.y = array_pos.y*App->map->data.tile_height;*/


	//need to fix
	int x = ((array_pos.x*16) - actual_tile.x))/16;

	
	int y = ((array_pos.y*16) - actual_tile.y)/16;

	pix_world_pos.x += x;
	pix_world_pos.y += y;
	/*
	this->pix_world_pos.x= this->array_pos.x*App->map->data.tile_width;
	this->pix_world_pos.y = this->array_pos.y*App->map->data.tile_height;

	*/
	if (pix_world_pos.x == (array_pos.x*16) && pix_world_pos.y == (array_pos.y*16)) {
		passedtile = true;
	}
	else {
		passedtile = false;
	}
	

}



