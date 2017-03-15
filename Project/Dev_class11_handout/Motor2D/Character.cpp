#include "Character.h"
#include "j1Map.h"
#include "j1App.h"

static const uint JUMP_DISTANCE = 48;

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
	this->adjacent.down.i = App->map->Colision->Get(tilepos.x, tilepos.y + 2);
	this->adjacent.down.j =  App->map->Colision->Get(tilepos.x + 1, tilepos.y + 2);
	this->adjacent.up.i = App->map->Colision->Get(tilepos.x, tilepos.y - 1);
	this->adjacent.up.j = App->map->Colision->Get(tilepos.x + 1, tilepos.y - 1);
	this->adjacent.left.i = App->map->Colision->Get(tilepos.x - 1, tilepos.y);
	this->adjacent.left.j =  App->map->Colision->Get(tilepos.x - 1, tilepos.y + 1);
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

uint Character::GetLogicHeightPlayer()
{
	return i_logic_height_player;
}

void Character::Jump(float dt)
{
	switch (character_direction) {
	case up:
		JumpFunction(dt, pos.y, false);
		break;
	case down:
		JumpFunction(dt, pos.y, true);
		break;
	case left:
		JumpFunction(dt, pos.x, false);
		break;
	case right:
		JumpFunction(dt, pos.x, true);
		break;
	}
}

void Character::MoveFunction(float dt, int& pos, int& other_pos, bool add, dir_tiles tiles, int side_tile_one, int side_tile_two, bool is_down)
{
	int tile_pos = (pos + 4) / 8;
	int other_tile_pos = (other_pos + 4) / 8;
	float speed = 1 / dt;
	int i = 1;
	if (!add)
		i = -1;
	int n = 1;
	if (is_down)
		n = -1;
	if (tiles.i != TILE_COL_ID && tiles.j != TILE_COL_ID) {
		pos = pos +  i *  speed*dt;
		if (side_tile_one == TILE_COL_ID && other_pos < other_tile_pos * 8)
			other_pos +=  speed*dt;
		if (side_tile_two == TILE_COL_ID && other_pos > other_tile_pos * 8)
			other_pos -= speed*dt;
	}
	else if (tiles.i == TILE_COL_ID && tiles.j != TILE_COL_ID) {
		if (n* ((!add* 7) + i* (other_pos +(!add * 8) - other_tile_pos * 8)) > n*(pos - tile_pos * 8))
			other_pos +=  speed*dt;
		else if (n* ((!add * 7) + i* (other_pos + (!add * 8) - other_tile_pos * 8)) < n*(pos - tile_pos * 8))
			pos += i * speed*dt;
		else {
			pos += i * speed*dt;
			other_pos += speed*dt;
		}
	}
	else if (tiles.i != TILE_COL_ID && tiles.j == TILE_COL_ID) {
		if (n*((add*7) -i*(other_pos + add*8 - other_tile_pos * 8)) > n*(pos - tile_pos * 8))
			other_pos -= speed*dt;
		else if (n*((add * 7) -i* (other_pos + add * 8 - other_tile_pos * 8)) <  n*(pos - tile_pos * 8))
			pos += i *  (speed*dt);
		else {
			pos += i* speed*dt;
			other_pos -= speed*dt;
		}
	}
	else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
		if ((pos - 1) / 8 == tile_pos)
			pos +=  i * speed*dt;
	}



}

void Character::MoveDiagonalFunction(float dt, int & pos_one, int & pos_two, bool add_one, bool add_two, int front_tile, int side_tile, int diagonal_tile)
{
	//pos_one y;
	//pos_two x;
	int i = 1;
	if (!add_one)
		i = -1;
	int n = 1;
	if (!add_two)
		n = -1;

	bool add = true;
	int negative = 1;
	if (add_one == add_two) {
		add = false;
	negative = -1;
	}


	float speed = 1 / dt;
	int tile_pos_one = (pos_one + 4) / 8;
	int tile_pos_side = (pos_two + 4) / 8;
	
	if (front_tile == TILE_COL_ID && side_tile == TILE_COL_ID) {
		if ((pos_one) / 8 == tile_pos_one && (pos_two + add_two*8) / 8 == tile_pos_side) {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
	}
	else if (front_tile == TILE_COL_ID && side_tile != TILE_COL_ID)
		pos_two += n*speed*dt;
	else if (front_tile != TILE_COL_ID && side_tile == TILE_COL_ID)
		pos_one += i*speed*dt;
	else if (front_tile != TILE_COL_ID && side_tile != TILE_COL_ID && diagonal_tile != TILE_COL_ID) {
		if ((add*7 +i*n*  (pos_two + add*8 - tile_pos_side * 8)) > (pos_one - tile_pos_one * 8))
			pos_two += n*speed*dt;
		else if ((add*7 + i*n* (pos_two + add*8 - tile_pos_side * 8)) < (pos_one - tile_pos_one * 8))
			pos_one += i*speed*dt;
		else {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
	}
	else if ( diagonal_tile == TILE_COL_ID) {
		if ((pos_one) / 8 == tile_pos_one && (pos_two + (add_two*8)) / 8 == tile_pos_side) {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
		else
			pos_one += i*speed*dt;
	}
	/*
	if (side_tile == TILE_COL_ID && side_tile.j == TILE_COL_ID)
		if ((pos_two + 8) / 8 == tile_pos_side)
			pos_two += n*speed*dt;
	if (front_tile.j == TILE_COL_ID && front_tile.i == TILE_COL_ID)
		if ((pos_one - 1) / 8 == tile_pos_one)
			pos_one += i*speed*dt;
*/
}

void Character::JumpFunction(float dt, int& pos, bool add)
{
	int i = 1;
	if (!add)
		i = -1;

	if (!temp)
		final_pos = pos + (i * JUMP_DISTANCE);
	temp = true;

	if (( i * pos <  i*final_pos)) {
		pos = pos + (i * 2);
	}
	else {
		temp = false;
		doing_script = false;
	}
}