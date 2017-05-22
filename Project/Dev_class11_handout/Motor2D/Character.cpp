#include "Character.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Collision.h"
#include "j1FileSystem.h"
#include"j1Player.h"
#include "j1Map.h"
#include "j1Window.h"
static const uint JUMP_DISTANCE = 112;



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
	case lifting:
		Move(dt);
		break;
	case attack:
		Attack(dt);
		break;

	case jump:
		Jump(dt);
		break;
	case roll:
		Roll(dt);
		break;

	case throw_:
		Throw(dt);
		break;
	case backwards:
		App->player->Link->Collision_Sword_EnemySword();
		break;
	case push_backwards:
		Direction_Push_Election();
		break;
	}

	//Dependiendo del evento actual i de la direccion cambia la animacion:
	//
	//Ejemplo: el evento Idle (1) - left (2) cogera la animación 1*4 + 2 = 6
	//El orden de estas animaciones se establece en el xml.
	if (actual_event != push_backwards) {
		int animation = (int)actual_event * 4 + (int)character_direction;
		this->ChangeAnimation(animation);
	}
}

void Character::GetAdjacents()
{
	//Take the tile_id of the adjacents. This depends on the logic height of each character.
	int height = this->GetLogicHeightPlayer();

	if (height < 0) {
		this->ChangeLogicHeightPlayer(0);
		height = 0;
	}

	this->adjacent.down.i = App->map->V_Colision[height]->Get(tilepos.x, tilepos.y + 2);
	this->adjacent.down.j =  App->map->V_Colision[height]->Get(tilepos.x + 1, tilepos.y + 2);
	this->adjacent.up.i = App->map->V_Colision[height]->Get(tilepos.x, tilepos.y - 1);
	this->adjacent.up.j = App->map->V_Colision[height]->Get(tilepos.x + 1, tilepos.y - 1);
	this->adjacent.left.i = App->map->V_Colision[height]->Get(tilepos.x - 1, tilepos.y);
	this->adjacent.left.j =  App->map->V_Colision[height]->Get(tilepos.x - 1, tilepos.y + 1);
	this->adjacent.right.i = App->map->V_Colision[height]->Get(tilepos.x + 2, tilepos.y);
	this->adjacent.right.j = App->map->V_Colision[height]->Get(tilepos.x + 2, tilepos.y + 1);
}

int Character::GetLogic(int minus_height, iPoint _pos)
{
	
	//Takes the id of the two front tiles of each player, depending on the locig height of each player
	std::vector<MapLayer*> vector = App->map->V_Colision;
	
	iPoint tile_pos = _pos;
	

	int i = 0, j = 0;
	switch (character_direction)
	{
	case up:
		i = vector[GetLogicHeightPlayer()- minus_height]->Get(tile_pos.x, tile_pos.y - 1);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x + 1, tile_pos.y - 1);
		break;
	case down:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x, tile_pos.y +2);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x +1, tile_pos.y +2);
		break;
	case left:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x - 1, tile_pos.y );
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x - 1, tile_pos.y +1);
		break;
	case right:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x + 2, tile_pos.y);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x + 2, tile_pos.y + 1);
		break;
	}
	
	if (i == App->map->CANT_PASS_COL_ID || j == App->map->CANT_PASS_COL_ID) return App->map->CANT_PASS_COL_ID;

	if (i != 0)return i;
	if (j != 0)return j;
	return 0;
}

int Character::GetBehindLogic(int minus_height, iPoint _pos)
{

	//Takes the id of the two front tiles of each player, depending on the locig height of each player
	std::vector<MapLayer*> vector = App->map->V_Colision;

	iPoint tile_pos = _pos;


	int i = 0, j = 0;
	switch (character_direction)
	{
	case up:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x, tile_pos.y + 2);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x + 1, tile_pos.y + 2);
		break;
	case down:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x, tile_pos.y -1);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x + 1, tile_pos.y -1);
		break;
	case left:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x +2, tile_pos.y);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x +2, tile_pos.y + 1);
		break;
	case right:
		i = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x - 1, tile_pos.y);
		j = vector[GetLogicHeightPlayer() - minus_height]->Get(tile_pos.x - 1, tile_pos.y + 1);
		break;
	}

	if (i == App->map->CANT_PASS_COL_ID || j == App->map->CANT_PASS_COL_ID) return App->map->CANT_PASS_COL_ID;

	if (i != 0)return i;
	if (j != 0)return j;
	return 0;
}

uint Character::GetLogicHeightPlayer()
{
	return logic_height;
}

void Character::ChangeLogicHeightPlayer(int height)
{
	logic_height = height;
}

void Character::UpdateColliderFront()
{

	//Updates the position of the front collider
	switch (character_direction) {
	case up:
		front_collider->rect = { 0,0,32,16 };
		front_collider->SetPos(tilepos.x * App->map->data.tile_width, tilepos.y * App->map->data.tile_height - App->map->data.tile_height, logic_height);
		break;
	case down:
		front_collider->rect = { 0,0,32,16 };
		front_collider->SetPos(tilepos.x *  App->map->data.tile_width, tilepos.y *  App->map->data.tile_height + 32, logic_height);
		break;
	case left:
		front_collider->rect = { 0,0,16,32 };
		front_collider->SetPos(tilepos.x *  App->map->data.tile_width - App->map->data.tile_width, tilepos.y *  App->map->data.tile_height, logic_height);
		break;
	case right:
		front_collider->rect = { 0,0,16,32 };
		front_collider->SetPos(tilepos.x *  App->map->data.tile_width + 32, tilepos.y *  App->map->data.tile_height, logic_height);
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

void Character::Throw(float dt)
{
	switch (character_direction) {
	case up:
		ThrowFunction(dt, pos.y, false,false);
		break;
	case down:
		ThrowFunction(dt, pos.y, true, false);
		break;
	case left:
		ThrowFunction(dt, pos.x, false, true);
		break;
	case right:
		ThrowFunction(dt, pos.x, true, true);
		break;
	}

}

bool Character::MoveFunction(float dt, int& pos, int& other_pos, bool add, dir_tiles tiles, int side_tile_one, int side_tile_two, bool is_down)
{

	
	bool ret = true;
	int tile_pos = (pos + (App->map->data.tile_width / 2)) / App->map->data.tile_width;
	int other_tile_pos = (other_pos + (App->map->data.tile_width / 2)) / App->map->data.tile_width;
	iPoint actual_pos = this->pos;
	float speed = 2 / dt;
	int i = 1;
	if (!add)
		i = -1;
	int n = 1;
	if (is_down)
		n = -1;
	if (tiles.i == 0 && tiles.j == 0) {
		pos = pos +  i *  speed*dt;
		if (side_tile_one != 0 && other_pos < other_tile_pos * App->map->data.tile_width)
			other_pos +=  speed*dt;
		if (side_tile_two != 0 && other_pos > other_tile_pos * App->map->data.tile_width)
			other_pos -= speed*dt;
	}
	else if (tiles.i != 0 && tiles.j == 0) {
		if (n* ((!add* 14) + i* (other_pos +(!add * App->map->data.tile_width) - other_tile_pos * App->map->data.tile_width)) > n*(pos - tile_pos * App->map->data.tile_width))
			other_pos +=  speed*dt;
		else if (n* ((!add * 14) + i* (other_pos + (!add * App->map->data.tile_width) - other_tile_pos * App->map->data.tile_width)) < n*(pos - tile_pos * App->map->data.tile_width))
			pos += i * speed*dt;
		else {
			pos += i * speed*dt;
			other_pos += speed*dt;
		}
	}
	else if (tiles.i == 0 && tiles.j != 0) {
		if (n*((add*14) -i*(other_pos + add*App->map->data.tile_width - other_tile_pos * App->map->data.tile_width)) > n*(pos - tile_pos * App->map->data.tile_width))
			other_pos -= speed*dt;
		else if (n*((add * 14) -i* (other_pos + add * 16 - other_tile_pos * App->map->data.tile_width)) <  n*(pos - tile_pos * App->map->data.tile_width))
			pos += i *  (speed*dt);
		else {
			pos += i* speed*dt;
			other_pos -= speed*dt;
		}
	}
	else if (tiles.i != 0 && tiles.j != 0) {
		if ((pos -1*!add + App->map->data.tile_width*add ) / App->map->data.tile_width == tile_pos)
			pos +=  i * speed*dt;
		else {
			ret = false;
		}		
	}
	float Scale = App->win->GetScale();
	if (this->pos.x > (-App->render->camera.x / Scale + App->render->camera.w / Scale) || this->pos.x < -App->render->camera.x / Scale)
					this->pos = actual_pos;
	if (this->pos.y > (-App->render->camera.y / Scale + App->render->camera.h / Scale) || this->pos.y < -App->render->camera.y / Scale)
			this->pos = actual_pos;
	return ret;
	
}

bool Character::MoveDiagonalFunction(float dt, int & pos_one, int & pos_two, bool add_one, bool add_two, int front_tile, int side_tile, int diagonal_tile, bool is_down)
{
	bool ret = false;
	iPoint actual_pos = this->pos;
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

	if (pos_one % 2 != 0)
		pos_one++;
	if (pos_two % 2 != 0)
		pos_two++;

	float speed = 2 / dt;
	int tile_pos_one = (pos_one + (App->map->data.tile_width / 2)) / App->map->data.tile_width;
	int tile_pos_side = (pos_two + (App->map->data.tile_width / 2)) / App->map->data.tile_width;

	if (front_tile != 0 && side_tile != 0) {
		if ((pos_one + add_one* App->map->data.tile_width) / App->map->data.tile_width == tile_pos_one && (pos_two + add_two* App->map->data.tile_width) / App->map->data.tile_width == tile_pos_side) {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
		else ret = false;
	}
	else if (front_tile != 0 && side_tile == 0)
		pos_two += n*speed*dt;
	else if (front_tile == 0 && side_tile != 0)
		pos_one += i*speed*dt;
	else if (front_tile == 0 && side_tile == 0 && diagonal_tile == 0) {
		if (change * (add * 14 + i*n*  (pos_two + add*App->map->data.tile_width - tile_pos_side * App->map->data.tile_width)) > change * (pos_one - tile_pos_one * App->map->data.tile_width))
		{
			if (pos_two % 2 == pos_one % 2)
				pos_two += n * 1;
			pos_two += n * 1;
		
	}
	else if (change * (add * 14 + i*n* (pos_two + add*App->map->data.tile_width - tile_pos_side * App->map->data.tile_width)) < change * (pos_one - tile_pos_one * App->map->data.tile_width))
	{
		if (pos_two % 2 == pos_one % 2)
			pos_one += i * 1;
		pos_one += i * 1;
		
	}
		else {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
	}
	else if ( diagonal_tile != 0) {
		if ((pos_one + add_one * App->map->data.tile_width) / App->map->data.tile_width == tile_pos_one && (pos_two + (add_two*App->map->data.tile_width)) / App->map->data.tile_width == tile_pos_side) {
			pos_one += i*speed*dt;
			pos_two += n*speed*dt;
		}
		else
			pos_one += i*speed*dt;
	}
	
	if (side_tile != 0 )
		if ((pos_two + add_two*App->map->data.tile_width - !add_two) / App->map->data.tile_width == tile_pos_side)
			pos_two += n*speed*dt;
	if (front_tile != 0)
		if ((pos_one + add_one*App->map->data.tile_width - !add_one) / App->map->data.tile_width == tile_pos_one)
			pos_one += i*speed*dt;

	float Scale = App->win->GetScale();
	if (this->pos.x > (-App->render->camera.x / Scale + App->render->camera.w / Scale) || this->pos.x < -App->render->camera.x / Scale)
		this->pos = actual_pos;
	if (this->pos.y >(-App->render->camera.y / Scale + App->render->camera.h / Scale) || this->pos.y < -App->render->camera.y / Scale)
		this->pos = actual_pos;

	return ret;
}

void Character::JumpFunction(float dt, int& pos, bool add)
{
	
	//with "temp" we calculate the final position of the jump just one time
	// "i" is used for changing the sign of the operation
	static bool cant_jump = false;
	int i = 1;
	if (!add)
		i = -1;

	if (!this->jump_temp) {
		jump_final_pos = pos + (i * JUMP_DISTANCE);
		float Scale = App->win->GetScale();
		if (this->pos.x + i*JUMP_DISTANCE> (-App->render->camera.x / Scale + App->render->camera.w / Scale) || this->pos.x < -App->render->camera.x / Scale) {
			//this->pos = actual_pos;
			//end_roll = true;
			cant_jump = true;
		}
		if (this->pos.y + i*JUMP_DISTANCE>(-App->render->camera.y / Scale + App->render->camera.h / Scale) || this->pos.y < -App->render->camera.y / Scale) {
			//this->pos = actual_pos;
			//end_roll = true;
			cant_jump = true;
		}
	}
	jump_temp = true;

	if (( i * pos <  i*jump_final_pos) && !cant_jump) {
		pos = pos + (i * 4);
	}
	// if player reached the final pos, player height decreases 1
	else if (cant_jump) {
		doing_script = false;
		cant_jump = false;
		jump_temp = false;
		actual_event = player_event::idle;
		can_walk = true;
		
	}
	else {
		jump_temp = false;
		doing_script = false;
		ChangeLogicHeightPlayer(GetLogicHeightPlayer() - 1);
		cant_jump = false;
	}
}

void Character::RollFunction(float dt, int & pos, bool add)
{
	
	static int final_pos = 0;
	iPoint actual_pos = this->pos;
	bool end_roll = false;
	//same as jump function
	int i = 1;
	if (!add)
		i = -1;

	if (!temp)
		final_pos = pos + (i * JUMP_DISTANCE);
	temp = true;

	float Scale = App->win->GetScale();
	if (this->pos.x > (-App->render->camera.x / Scale + App->render->camera.w / Scale) || this->pos.x < -App->render->camera.x / Scale) {
		this->pos = actual_pos;
		end_roll = true;
	}
	if (this->pos.y > (-App->render->camera.y / Scale + App->render->camera.h / Scale) || this->pos.y < -App->render->camera.y / Scale) {
		this->pos = actual_pos;
		end_roll = true;
	}
	//if player have wall in front the roll will stop
	if ((i * pos <  i*final_pos) && GetLogic(false, tilepos) == 0  && !end_roll) {
		pos = pos + (i * 4);
	}
	else {
		temp = false;
		doing_script = false;
		is_rolling = false;
		//roll_timer.Start();
	}

}

void Character::ThrowFunction(float dt, int & pos, bool add, bool is_horitzontal)
{
}

void Character::Collision_Sword_EnemySword() {
	iPoint temp = tilepos;

	/*
	switch (character_direction) {


	case direction::up:
		temp.y = tilepos.y + 2;
		if (GetLogic(GetLogicHeightPlayer(), temp) != App->map->TILE_COL_ID) {
			pos.y += 14;
		}
		break;

	case direction::down:
		temp.y = tilepos.y - 1;
		if (GetLogic(GetLogicHeightPlayer(), temp) != App->map->TILE_COL_ID) {
			pos.y -= 14;
		}
		break;

	case direction::right:
		temp.x = tilepos.x - 1;
		if (GetLogic(GetLogicHeightPlayer(), temp) != App->map->TILE_COL_ID) {
			pos.x -= 14;
		}
		break;

	case direction::left:
		temp.x = tilepos.x + 2;
		if (GetLogic(GetLogicHeightPlayer(), temp) != App->map->TILE_COL_ID) {
			pos.x += 14;
		}
		break;


	}*/

}


void Character::Direction_Push_Election()
{
	//Calls the jump function depending on the player direction
	switch (character_direction) {
	case direction::up:
		Player_Hurt_Displacement(pos.y, true);
		break;
	case direction::down:
		Player_Hurt_Displacement(pos.y, false);
		break;
	case direction::left:
		Player_Hurt_Displacement(pos.x, true);
		break;
	case direction::right:
		Player_Hurt_Displacement(pos.x, false);
		break;
	}
}


void Character::Player_Hurt_Displacement(int & pos, bool add)
{

	static int final_pos = 0;
	static bool cant_be_pushed = false;
	//same as jump function
	int i = 1;
	if (!add)
		i = -1;

	if (!temp) {
		final_pos = pos + (i * PUSH_DISTANCE);
		float Scale = App->win->GetScale();
		if (this->pos.x + (i * PUSH_DISTANCE)> (-App->render->camera.x / Scale + App->render->camera.w / Scale) || this->pos.x < -App->render->camera.x / Scale) {
			//this->pos = actual_pos;
			//end_roll = true;
			cant_be_pushed = true;
		}
		if (this->pos.y + (i * PUSH_DISTANCE)>(-App->render->camera.y / Scale + App->render->camera.h / Scale) || this->pos.y < -App->render->camera.y / Scale) {
			//this->pos = actual_pos;
			//end_roll = true;
			cant_be_pushed = true;
		}
	}
	temp = true;

	//if player have wall in front the roll will stop
	if ((i * pos <  i*final_pos) && GetBehindLogic(false, tilepos) == 0 && !cant_be_pushed) {
		pos = pos + (i * 4);
	}
	else if (cant_be_pushed) {
		doing_script = false;
		temp = false;
		cant_be_pushed = false;
	}
	else {
		doing_script = false;
		temp = false;
		cant_be_pushed = false;
	}

}