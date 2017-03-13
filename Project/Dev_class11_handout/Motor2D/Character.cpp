#include "Character.h"
#include "j1Map.h"
#include "j1App.h"

void Character::LoadAnimation(const char* path)
{
}

void Character::ChangeAnimation(int)
{
}

player_event Character::GetEvent()
{
	return player_event();
}

void Character::ExecuteEvent(float dt)
{
	switch (actual_event) {
	case move:
		Move(dt);
		break;

	case attack:
		break;

	case jump:
		break;
	}

	int animation = (int)actual_event * 4 + (int)character_direction;
	this->ChangeAnimation(animation);
}

void Character::GetAdjacents()
{

	//adjacent_tiles adjacent;

	

	this->adjacent.down.i = App->map->Colision->Get(tilepos.x + 1, tilepos.y + 2);
	this->adjacent.down.j = App->map->Colision->Get(tilepos.x, tilepos.y + 2);
	this->adjacent.up.i = App->map->Colision->Get(tilepos.x, tilepos.y - 1);
	this->adjacent.up.j = App->map->Colision->Get(tilepos.x + 1, tilepos.y - 1);
	this->adjacent.left.i = App->map->Colision->Get(tilepos.x - 1, tilepos.y + 1);
	this->adjacent.left.j = App->map->Colision->Get(tilepos.x - 1, tilepos.y);
	this->adjacent.right.i = App->map->Colision->Get(tilepos.x + 2, tilepos.y);
	this->adjacent.right.j = App->map->Colision->Get(tilepos.x + 2, tilepos.y + 1);

}

