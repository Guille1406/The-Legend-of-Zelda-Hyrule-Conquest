#include "Character.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Collision.h"

static const uint JUMP_DISTANCE = 112;

void Character::LoadAnimation(const char* path)
{
}

void Character::ChangeAnimation(int animation)
{
		//If the animation is diferent than the actual, change it
		if (last_animation != animation) {
		this->actual_animation = this->sprites_vector[0][animation];
		last_animation = animation;
	}
}

player_event Character::GetEvent()
{
	return player_event();
}

void Character::ExecuteEvent(float dt)
{
	//Execute the diferent functions depending on the actual_event of each character
	switch (actual_event) {
	case move:
		Move(dt);
		break;

	case attack:

		break;

	case jump:
		Jump(dt);
		break;
	case roll:
		Roll(dt);
		break;

	}

	//Dependiendo del evento actual i de la direccion cambia la animacion:
	//
	//Ejemplo: el evento Idle (1) - left (2) cogera la animación 1*4 + 2 = 6
	//El orden de estas animaciones se establece en el xml.
		int animation = (int)actual_event * 4 + (int)character_direction;
	this->ChangeAnimation(animation);
}

void Character::GetAdjacents()
{
	//Take the tile_id of the adjacents. This depends on the logic height of each character.

	this->adjacent.down.i = App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x, tilepos.y + 2);
	this->adjacent.down.j =  App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x + 1, tilepos.y + 2);
	this->adjacent.up.i = App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x, tilepos.y - 1);
	this->adjacent.up.j = App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x + 1, tilepos.y - 1);
	this->adjacent.left.i = App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x - 1, tilepos.y);
	this->adjacent.left.j =  App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x - 1, tilepos.y + 1);
	this->adjacent.right.i = App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x + 2, tilepos.y);
	this->adjacent.right.j = App->map->V_Colision[GetLogicHeightPlayer()]->Get(tilepos.x + 2, tilepos.y + 1);
}

int Character::GetLogic(bool collisions)
{
	
	//Takes the id of the two front tiles of each player, depending on the locig height of each player
	std::vector<MapLayer*> vector = App->map->V_Colision;
			

	int i, j;
	switch (character_direction)
	{
	case up:
		i = vector[GetLogicHeightPlayer()]->Get(tilepos.x, tilepos.y - 1);
		j = vector[GetLogicHeightPlayer()]->Get(tilepos.x + 1, tilepos.y - 1);
		break;
	case down:
		i = vector[GetLogicHeightPlayer()]->Get(tilepos.x, tilepos.y +2);
		j = vector[GetLogicHeightPlayer()]->Get(tilepos.x +1, tilepos.y +2);
		break;
	case left:
		i = vector[GetLogicHeightPlayer()]->Get(tilepos.x - 1, tilepos.y );
		j = vector[GetLogicHeightPlayer()]->Get(tilepos.x - 1, tilepos.y +1);
		break;
	case right:
		i = vector[GetLogicHeightPlayer()]->Get(tilepos.x + 2, tilepos.y);
		j = vector[GetLogicHeightPlayer()]->Get(tilepos.x + 2, tilepos.y + 1);
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

void Character::ChangeLogicHeightPlayer(int height)
{
	i_logic_height_player = height;
}

void Character::UpdateColliderFront()
{

	//Updates the position of the front collider
	switch (character_direction) {
	case up:
		front_collider->rect = { 0,0,32,16 };
		front_collider->SetPos(tilepos.x * 16, tilepos.y * 16 - 16, i_logic_height_player);
		break;
	case down:
		front_collider->rect = { 0,0,32,16 };
		front_collider->SetPos(tilepos.x * 16, tilepos.y * 16 + 32, i_logic_height_player);
		break;
	case left:
		front_collider->rect = { 0,0,16,32 };
		front_collider->SetPos(tilepos.x * 16 - 16, tilepos.y * 16, i_logic_height_player);
		break;
	case right:
		front_collider->rect = { 0,0,16,32 };
		front_collider->SetPos(tilepos.x * 16 + 32, tilepos.y * 16, i_logic_height_player);
		break;
	}

}

void Character::Jump(float dt)
{
	//Calls the jump function depending on the player direction
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

void Character::Roll(float dt)
{
	//Calls the roll function depending on the player direction
	switch (character_direction) {
	case up:
		RollFunction(dt, pos.y, false);
		break;
	case down:
		RollFunction(dt, pos.y, true);
		break;
	case left:
		RollFunction(dt, pos.x, false);
		break;
	case right:
		RollFunction(dt, pos.x, true);
		break;
	}
}

bool Character::MoveFunction(float dt, int& pos, int& other_pos, bool add, dir_tiles tiles, int side_tile_one, int side_tile_two, bool is_down)
{

	
	bool ret = true;
	int tile_pos = (pos + 8) / 16;
	int other_tile_pos = (other_pos + 8) / 16;
	float speed = 2 / dt;
	int i = 1;
	if (!add)
		i = -1;
	int n = 1;
	if (is_down)
		n = -1;
	if (tiles.i != TILE_COL_ID && tiles.j != TILE_COL_ID) {
		pos = pos +  i *  speed*dt;
		if (side_tile_one == TILE_COL_ID && other_pos < other_tile_pos * 16)
			other_pos +=  speed*dt;
		if (side_tile_two == TILE_COL_ID && other_pos > other_tile_pos * 16)
			other_pos -= speed*dt;
	}
	else if (tiles.i == TILE_COL_ID && tiles.j != TILE_COL_ID) {
		if (n* ((!add* 14) + i* (other_pos +(!add * 16) - other_tile_pos * 16)) > n*(pos - tile_pos * 16))
			other_pos +=  speed*dt;
		else if (n* ((!add * 14) + i* (other_pos + (!add * 16) - other_tile_pos * 16)) < n*(pos - tile_pos * 16))
			pos += i * speed*dt;
		else {
			pos += i * speed*dt;
			other_pos += speed*dt;
		}
	}
	else if (tiles.i != TILE_COL_ID && tiles.j == TILE_COL_ID) {
		if (n*((add*14) -i*(other_pos + add*16 - other_tile_pos * 16)) > n*(pos - tile_pos * 16))
			other_pos -= speed*dt;
		else if (n*((add * 14) -i* (other_pos + add * 16 - other_tile_pos * 16)) <  n*(pos - tile_pos * 16))
			pos += i *  (speed*dt);
		else {
			pos += i* speed*dt;
			other_pos -= speed*dt;
		}
	}
	else if (tiles.i == TILE_COL_ID && tiles.j == TILE_COL_ID) {
		if ((pos -1*!add + 16*add ) / 16 == tile_pos)
			pos +=  i * speed*dt;
		else {
			ret = false;
		}		
	}
	return ret;
	
}

bool Character::MoveDiagonalFunction(float dt, int & pos_one, int & pos_two, bool add_one, bool add_two, int front_tile, int side_tile, int diagonal_tile, bool is_down)
{
	bool ret = false;
	//pos_one y;
	//pos_two x;
	int i = 1;
	if (!add_one)
		i = -1;
	int n = 1;
	if (!add_two)
		n = -1;

	int change = 1;
	if (is_down)
		change = -1;

	bool add = true;
	int negative = 1;
	if (add_one == add_two) {
		add = false;
	negative = -1;
	}

	float speed = 2 / dt;
	int tile_pos_one = (pos_one + 8) / 16;
	int tile_pos_side = (pos_two + 8) / 16;
	
	if (front_tile == TILE_COL_ID && side_tile == TILE_COL_ID) {
		if ((pos_one + add_one*16 ) / 16 == tile_pos_one && (pos_two + add_two*16) / 16 == tile_pos_side) {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
		else ret = false;
	}
	else if (front_tile == TILE_COL_ID && side_tile != TILE_COL_ID)
		pos_two += n*speed*dt;
	else if (front_tile != TILE_COL_ID && side_tile == TILE_COL_ID)
		pos_one += i*speed*dt;
	else if (front_tile != TILE_COL_ID && side_tile != TILE_COL_ID && diagonal_tile != TILE_COL_ID) {
		if (change * (add*14 +i*n*  (pos_two + add*16 - tile_pos_side * 16)) > change * (pos_one - tile_pos_one * 16))
			pos_two += n*speed*dt;
		else if (change * (add*14 + i*n* (pos_two + add*16 - tile_pos_side * 16)) < change * (pos_one - tile_pos_one * 16))
			pos_one += i*speed*dt;
		else {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
	}
	else if ( diagonal_tile == TILE_COL_ID) {
		if ((pos_one + add_one * 16) / 16 == tile_pos_one && (pos_two + (add_two*16)) / 16 == tile_pos_side) {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
		else
			pos_one += i*speed*dt;
	}
	
	if (side_tile == TILE_COL_ID )
		if ((pos_two + add_two*16 - !add_two) / 16 == tile_pos_side)
			pos_two += n*speed*dt;
	if (front_tile == TILE_COL_ID)
		if ((pos_one + add_one*16 - !add_one) / 16 == tile_pos_one)
			pos_one += i*speed*dt;


	return ret;
}

void Character::JumpFunction(float dt, int& pos, bool add)
{
	//with "temp" we calculate the final position of the jump just one time
	// "i" is used for changing the sign of the operation

	int i = 1;
	if (!add)
		i = -1;

	if (!temp)
		final_pos = pos + (i * JUMP_DISTANCE);
	temp = true;

	if (( i * pos <  i*final_pos)) {
		pos = pos + (i * 4);
	}
	// if player reached the final pos, player height decreases 1
	else {
		temp = false;
		doing_script = false;
		ChangeLogicHeightPlayer(GetLogicHeightPlayer() - 1);
	}
}

void Character::RollFunction(float dt, int & pos, bool add)
{
	//same as jump function
	int i = 1;
	if (!add)
		i = -1;

	if (!temp)
		final_pos = pos + (i * JUMP_DISTANCE);
	temp = true;

	//if player have wall in front the roll will stop
	if ((i * pos <  i*final_pos) && GetLogic(true) != TILE_COL_ID ) {
		pos = pos + (i * 4);
	}
	else {
		temp = false;
		doing_script = false;
	}

}
