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
		Jump(dt);
		break;
	}

	int animation = (int)actual_event * 4 + (int)character_direction;
	this->ChangeAnimation(animation);
}

void Character::GetAdjacents()
{
	this->adjacent.down.i = App->map->Colision->Get(tilepos.x + 1, tilepos.y + 2);
	this->adjacent.down.j = App->map->Colision->Get(tilepos.x, tilepos.y + 2);
	this->adjacent.up.i = App->map->Colision->Get(tilepos.x, tilepos.y - 1);
	this->adjacent.up.j = App->map->Colision->Get(tilepos.x + 1, tilepos.y - 1);
	this->adjacent.left.i = App->map->Colision->Get(tilepos.x - 1, tilepos.y + 1);
	this->adjacent.left.j = App->map->Colision->Get(tilepos.x - 1, tilepos.y);
	this->adjacent.right.i = App->map->Colision->Get(tilepos.x + 2, tilepos.y);
	this->adjacent.right.j = App->map->Colision->Get(tilepos.x + 2, tilepos.y + 1);
}

int Character::GetLogic()
{
	int i, j;
	switch (character_direction)
	{
	case up:
		i = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x, tilepos.y - 1);
		j = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x + 1, tilepos.y - 1);
		break;
	case down:
		i = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x, tilepos.y +2);
		j = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x +1, tilepos.y +2);
		break;
	case left:
		i = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x - 1, tilepos.y );
		j = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x - 1, tilepos.y +1);
		break;
	case right:
		i = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x + 2, tilepos.y);
		j = App->map->V_Logic[GetLogicHeightPlayer()]->Get(tilepos.x + 2, tilepos.y + 1);
		break;
	}
	if (i != 0)return i;
	if (j != 0)return j;
	return 0;
}

void Character::Jump(float)
{
	int jump_distance = 48;
	static int final_pos;

	//Sirve para guardar la posicion final solo una vez
	static bool temp = false;

	switch (character_direction) {
	case up:		
		if(!temp)final_pos = pos.y - jump_distance;
		temp = true;
		if (pos.y > final_pos) {
			pos.y -= 2;
		}
		else {
			temp = false;
			doing_script = false;
		}
		break;

	case down:
		if (!temp)
			final_pos = pos.y + jump_distance;
		temp = true;
		if (pos.y < final_pos) {
			pos.y+= 2;
		}
		else {
			temp = false;
			doing_script = false;
		}
		break;
	case left:
		if (!temp)final_pos = pos.x - jump_distance;
		temp = true;
		if (pos.x > final_pos) {
			pos.x-= 2;
		}
		else {
			temp = false;
			doing_script = false;
		}
		break;
	case right:
		if (!temp)final_pos = pos.x + jump_distance;
		temp = true;
		if (pos.x < final_pos) {
			pos.x+= 2;
		}
		else {
			temp = false;
			doing_script = false;
		}
		break;
	}
}

uint Character::GetLogicHeightPlayer()
{
	return i_logic_height_player;
}

