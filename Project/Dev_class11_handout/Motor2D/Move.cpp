#include "j1Player.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "p2Log.h"
#define TILE_COL_ID 237



void j1Player::Move(Character* character, float dt)
{
	
	key_state state = idle;
	adjacent_tiles adjacent;

	
	
	Character* Selected_Character = character;
	if (character == Link) {
		adjacent = adjacent_link;
		state = Get_Movement_Event_Link();

	}
	else if (character == Zelda) {
		if (cooperative == true) {
			adjacent = adjacent_zelda;
			state = Get_Movement_Event_Zelda();
		}
		else
		{
			adjacent = adjacent_zelda;
			state = Get_Movement_Event_Link();
		}
	}


	p2Point<int> pos = Selected_Character->pos;

	Selected_Character->tilepos.x = (pos.x + 3) / 8;
	Selected_Character->tilepos.y = (pos.y + 3) / 8;

	int tile_pos_x = Selected_Character->tilepos.x;
	int tile_pos_y = Selected_Character->tilepos.y;

	int pos_x = Selected_Character->pos.x;
	int pos_y = Selected_Character->pos.y;


	//DIAGONAL TILES
	uint diagonal_right_up = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y -1);
	uint diagonal_left_up  = App->map->Colision->Get(tile_pos_x -1, tile_pos_y - 1);
	uint diagonal_right_down = App->map->Colision->Get(tile_pos_x +2, tile_pos_y +2);
	uint diagonal_left_down = App->map->Colision->Get(tile_pos_x -1, tile_pos_y +2);
	
	

	float speed = 1/dt;
	
	switch (state) {
	case up:
		if (adjacent.up.i != TILE_COL_ID && adjacent.up.j != TILE_COL_ID)
			Selected_Character->pos.y -=  speed*dt;
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j != TILE_COL_ID) {
			if (7 - (pos_x +6- tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if (7 - (pos_x + 6 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y -= speed*dt;;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if (pos_x - tile_pos_x * 8 > pos_y - tile_pos_y * 8) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if (pos_x - tile_pos_x * 8 < pos_y - tile_pos_y * 8) {
				Selected_Character->pos.y -= speed*dt;;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y) {
				Selected_Character->pos.y-= speed*dt;
			}
		}
		break;

	case down:
		if (adjacent.down.i != TILE_COL_ID && adjacent.down.j != TILE_COL_ID)
			Selected_Character->pos.y += speed*dt;
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j != TILE_COL_ID) {
			if (7 - (pos_x +6 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if (7 - (pos_x + 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_y + 8)  / 8 == tile_pos_y ) {
				Selected_Character->pos.y += speed*dt;
			}
		}

		break;

	case left:
		if (adjacent.left.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID)
			Selected_Character->pos.x -= speed*dt;
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {
				Selected_Character->pos.x -= speed*dt;
				Selected_Character->pos.y -= speed*dt;
			}
		}
		else if (adjacent.left.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {

			if (7 - (pos_x + 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if (7 - (pos_x +6 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_x - 1) / 8 == tile_pos_x) {
				Selected_Character->pos.x -= speed*dt;
			}
		}
		break;
	case right:
		if (adjacent.right.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID)
			Selected_Character->pos.x += speed*dt;
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if ((pos_x  - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.right.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if (7 - (pos_x + 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if (7 - (pos_x + 6 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((pos_x +8) / 8 == tile_pos_x ) {
				Selected_Character->pos.x += speed*dt;
			}
		}
		break;

	case left_up:
		if (adjacent.up.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y && (pos_x - 1) / 8 == tile_pos_x) {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}

		else if (adjacent.up.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			Selected_Character->pos.x -= speed*dt;
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			Selected_Character->pos.y -= speed*dt;
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID && diagonal_left_up != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {

				pos.y = pos.x - Selected_Character->tilepos.x * 8 + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.x -= speed*dt;
				Selected_Character->pos.y -= speed*dt;
			}
		}
		
		else if (diagonal_left_up == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y && (pos_x - 1) / 8 == tile_pos_x) {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
			}
		}

		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_x - 1) / 8 == tile_pos_x) {
				Selected_Character->pos.x -= speed*dt;
			}
		}
		if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y) {
				Selected_Character->pos.y -= speed*dt;
			}
		}
		break;

	case right_up:
		if (adjacent.up.j == TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			if ((pos_y) / 8 == tile_pos_y && (pos_x + 8) / 8 == tile_pos_x) {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}

		else if (adjacent.up.j == TILE_COL_ID && adjacent.right.i != TILE_COL_ID) {
			Selected_Character->pos.x += speed*dt;
		}
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			Selected_Character->pos.y -= speed*dt;
		}
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i != TILE_COL_ID && diagonal_right_up != TILE_COL_ID) {
			if (7 - (pos_x+ 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if (7 - (pos_x+6 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {
			
				Selected_Character->pos.x += speed*dt;
				Selected_Character->pos.y -= speed*dt;
			}
		}
		
		 else if (diagonal_right_up == TILE_COL_ID) {
			if ((pos_y ) / 8 == tile_pos_y && (pos_x +8) / 8 == tile_pos_x) {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
			}
		}

			if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			 if ((pos_x + 8) / 8 == tile_pos_x) {
				 Selected_Character->pos.x += speed*dt;
			 }
		 }
			if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			 if ((pos_y - 1) / 8 == tile_pos_y) {
				 Selected_Character->pos.y -= speed*dt;
			 }
		 }
		break;
	case left_down:

		if (adjacent.down.j == TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x) / 8 == tile_pos_x) {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}

		else if (adjacent.down.j == TILE_COL_ID && adjacent.left.i != TILE_COL_ID) {
			Selected_Character->pos.x -= speed*dt;
			
		}
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			Selected_Character->pos.y += speed*dt;
			
		}
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i != TILE_COL_ID && diagonal_left_down != TILE_COL_ID) {
			if (7 - (pos_x + 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if (7 - (pos_x + 6- tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				Selected_Character->pos.x -= speed*dt;
				Selected_Character->pos.y += speed*dt;
			}
		}
		
		else if (diagonal_left_down == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x ) / 8 == tile_pos_x) {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
			}
		}
		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_x - 1) / 8 == tile_pos_x) {
				Selected_Character->pos.x -= speed*dt;
			}
		}
		if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y) {
				Selected_Character->pos.y += speed*dt;
			}
		}
		break;

	case right_down:
		if (adjacent.down.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x + 8) / 8 == tile_pos_x) {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}

		else if (adjacent.down.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			Selected_Character->pos.x += speed*dt;
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			Selected_Character->pos.y += speed*dt;
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID && diagonal_right_down != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if ((pos_x  - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else {
				
				Selected_Character->pos.x += speed*dt;
				Selected_Character->pos.y += speed*dt;
			}
		}
		
		else if (diagonal_right_down == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x + 8) / 8 == tile_pos_x) {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
			}
		}
		if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((pos_x + 8) / 8 == tile_pos_x) {
				Selected_Character->pos.x += speed*dt;
			}
		}
		if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y) {
				Selected_Character->pos.y += speed*dt;
			}
		}
	
		break;
	}	
}

