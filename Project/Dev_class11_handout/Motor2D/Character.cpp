#include "Character.h"
#include "j1Map.h"
#include "j1App.h"

void Character::LoadAnimation(const char* path)
{
}

void Character::ChangeAnimation(movement_animation)
{
}

key_state Character::GetEvent()
{
	return key_state();
}

void Character::GetAdjacents()
{

	//adjacent_tiles adjacent;

	uint tile_pos_x = (pos.x + 3) / 8;
	uint tile_pos_y = (pos.y + 3) / 8;

	this->adjacent.down.i = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y + 2);
	this->adjacent.down.j = App->map->Colision->Get(tile_pos_x, tile_pos_y + 2);
	this->adjacent.up.i = App->map->Colision->Get(tile_pos_x, tile_pos_y - 1);
	this->adjacent.up.j = App->map->Colision->Get(tile_pos_x + 1, tile_pos_y - 1);
	this->adjacent.left.i = App->map->Colision->Get(tile_pos_x - 1, tile_pos_y + 1);
	this->adjacent.left.j = App->map->Colision->Get(tile_pos_x - 1, tile_pos_y);
	this->adjacent.right.i = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y);
	this->adjacent.right.j = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y + 1);

}

