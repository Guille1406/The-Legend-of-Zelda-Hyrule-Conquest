#include "j1Player.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "p2Log.h"
#include "Character.h"


void Character::Move(float dt)
{
	uint x, y;
	App->win->GetWindowSize(x, y);

	// SHORT VARIABLES
	int pos_x = this->pos.x;
	int pos_y = this->pos.y;

	int tile_pos_x = this->tilepos.x;
	int tile_pos_y = this->tilepos.y;

	////Camera
	
	
	//DIAGONAL TILES
	uint diagonal_right_up = App->map->V_Colision[GetLogicHeightPlayer()]->Get(this->tilepos.x + 2, tile_pos_y -1);
	uint diagonal_left_up  = App->map->V_Colision[GetLogicHeightPlayer()]->Get(this->tilepos.x -1, tile_pos_y - 1);
	uint diagonal_right_down = App->map->V_Colision[GetLogicHeightPlayer()]->Get(this->tilepos.x +2, tile_pos_y +2);
	uint diagonal_left_down = App->map->V_Colision[GetLogicHeightPlayer()]->Get(this->tilepos.x -1, tile_pos_y +2);
	
	/////
	float speed = 4/dt;

	switch (movement_direction) {
	case move_up:

		can_move = MoveFunction(dt, pos.y, pos.x, false, adjacent.up, adjacent.left.i, adjacent.right.i);
	
		break;

	case  move_down:
		can_move = MoveFunction(dt, pos.y, pos.x, true, adjacent.down, adjacent.left.j,  adjacent.right.j, true);
	
		break;

	case move_left:
		can_move = MoveFunction(dt, pos.x, pos.y, false, adjacent.left, adjacent.up.i, adjacent.down.i);
		
		break;

	case move_right:
		can_move = MoveFunction(dt, pos.x, pos.y, true, adjacent.right, adjacent.up.j, adjacent.down.j, true);
		
		break;

	case move_up_left:
		can_move = MoveDiagonalFunction(dt, pos.y, pos.x, false, false, adjacent.up.i, adjacent.left.i, diagonal_left_up);
		
		break;

	case move_up_right:
		can_move = MoveDiagonalFunction(dt, pos.y, pos.x, false, true, adjacent.up.j, adjacent.right.i, diagonal_right_up);
		
		break;

	case move_down_left:
		can_move = MoveDiagonalFunction(dt, pos.y, pos.x, true, false, adjacent.down.i, adjacent.left.j, diagonal_left_down, true);
		
		break;

	case move_down_right:
		can_move = MoveDiagonalFunction(dt, pos.y, pos.x, true, true, adjacent.down.j, adjacent.right.j, diagonal_right_down, true);
		
		break;
	}

	
}


