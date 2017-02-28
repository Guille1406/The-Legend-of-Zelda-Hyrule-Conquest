#include "j1Player.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"

#define TILE_COL_ID 237



void j1Player::Move(Character* character, float dt)
{


	key_state state = idle;
	// HAY QUE INTENTAR QUE ESTO NO SEA TAN HARD CODE
	//ADEMAS HAY ALGUNOS BUGS :S


	

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
	p2Point<int> o_pos = other_character->pos;

	Selected_Character->tilepos.x = (pos.x + 3) / 8;
	Selected_Character->tilepos.y = (pos.y + 3) / 8;

	other_character->tilepos.x = (o_pos.x + 3) / 8;
	other_character->tilepos.y = (o_pos.y + 3) / 8;

	int tile_pos_x = Selected_Character->tilepos.x;
	int tile_pos_y = Selected_Character->tilepos.y;



	//DIAGONAL TILES

	uint d_r_u = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y -1);
	uint d_l_u  = App->map->Colision->Get(tile_pos_x -1, tile_pos_y - 1);
	uint d_r_d = App->map->Colision->Get(tile_pos_x +2, tile_pos_y +2);
	uint d_l_d = App->map->Colision->Get(tile_pos_x -1, tile_pos_y +2);
	
	
	
	//}
	if (state == left_up) {
		int a = 0;
	}
	int t_x = Selected_Character->tilepos.x;
	int t_y = Selected_Character->tilepos.y;
	int p_x = Selected_Character->pos.x;
	int p_y = Selected_Character->pos.y;


	float speed = 1/dt;
	
	switch (state) {
	case up:
		if (adjacent.up.i != TILE_COL_ID && adjacent.up.j != TILE_COL_ID)
			Selected_Character->pos.y -=  speed*dt;
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j != TILE_COL_ID) {
			if (7 - (p_x +6- t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if (7 - (p_x + 6 - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.y -= speed*dt;;
			}
			else {
				//pos.y = 7 - (pos.x - Selected_Character->tilepos.x * 8) + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if (p_x - t_x * 8 > p_y - t_y * 8) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if (p_x - t_x * 8 < p_y - t_y * 8) {
				Selected_Character->pos.y -= speed*dt;;
			}
			else {
				//pos.y = pos.x - Selected_Character->tilepos.x * 8 + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((p_y - 1) / 8 == t_y) {
				Selected_Character->pos.y-= speed*dt;
			}
		}
		break;

	case down:
		if (adjacent.down.i != TILE_COL_ID && adjacent.down.j != TILE_COL_ID)
			Selected_Character->pos.y += speed*dt;
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j != TILE_COL_ID) {
			if (7 - (p_x +6 - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if (7 - (p_x + 6 - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else {
				// pos.y = 7 - (pos.x - Selected_Character->tilepos.x * 8) + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else {
				// pos.y = pos.x - Selected_Character->tilepos.x * 8 + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((p_y + 8)  / 8 == t_y ) {
				Selected_Character->pos.y += speed*dt;
			}
		}

		break;

	case left:
		if (adjacent.left.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID)
			Selected_Character->pos.x -= speed*dt;
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {
				//pos.y = pos.x - Selected_Character->tilepos.x * 8 + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.x -= speed*dt;
				Selected_Character->pos.y -= speed*dt;
			}
		}
		else if (adjacent.left.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {

			if (7 - (p_x + 6 - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if (7 - (p_x +6 - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				// pos.y = 7 - (pos.x - Selected_Character->tilepos.x * 8) + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
		}
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_x - 1) / 8 == t_x) {
				Selected_Character->pos.x -= speed*dt;
			}
		}
		break;
	case right:
		if (adjacent.right.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID)
			Selected_Character->pos.x += speed*dt;
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if ((p_x  - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else {
				//pos.y = pos.x - Selected_Character->tilepos.x * 8 + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.right.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if (7 - (p_x + 6 - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if (7 - (p_x + 6 - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {
				// pos.y = 7 - (pos.x - Selected_Character->tilepos.x * 8) + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
		}
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((p_x +8) / 8 == t_x ) {
				Selected_Character->pos.x += speed*dt;
			}
		}
		break;

	case left_up:
		if (adjacent.up.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_y - 1) / 8 == t_y && (p_x - 1) / 8 == t_x) {
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
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID && d_l_u != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {

				pos.y = pos.x - Selected_Character->tilepos.x * 8 + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.x -= speed*dt;
				Selected_Character->pos.y -= speed*dt;
			}
		}
		
		else if (d_l_u == TILE_COL_ID) {
			if ((p_y - 1) / 8 == t_y && (p_x - 1) / 8 == t_x) {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
			}
		}

		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_x - 1) / 8 == t_x) {
				Selected_Character->pos.x -= speed*dt;
			}
		}
		if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((p_y - 1) / 8 == t_y) {
				Selected_Character->pos.y -= speed*dt;
			}
		}
		break;

	case right_up:
		if (adjacent.up.j == TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			if ((p_y) / 8 == t_y && (p_x + 8) / 8 == t_x) {
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
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i != TILE_COL_ID && d_r_u != TILE_COL_ID) {
			if (7 - (p_x+ 6 - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if (7 - (p_x+6 - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.y -= speed*dt;
			}
			else {
			
				Selected_Character->pos.x += speed*dt;
				Selected_Character->pos.y -= speed*dt;
			}
		}
		
		 else if (d_r_u == TILE_COL_ID) {
			if ((p_y ) / 8 == t_y && (p_x +8) / 8 == t_x) {
				Selected_Character->pos.y -= speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
			else {
				Selected_Character->pos.y -= speed*dt;
			}
		}

			if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			 if ((p_x + 8) / 8 == t_x) {
				 Selected_Character->pos.x += speed*dt;
			 }
		 }
			if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			 if ((p_y - 1) / 8 == t_y) {
				 Selected_Character->pos.y -= speed*dt;
			 }
		 }
		break;
	case left_down:

		if (adjacent.down.j == TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			if ((p_y + 8) / 8 == t_y && (p_x) / 8 == t_x) {
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
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i != TILE_COL_ID && d_l_d != TILE_COL_ID) {
			if (7 - (p_x + 6 - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else if (7 - (p_x + 6- t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				// pos.y = 7 - (pos.x - Selected_Character->tilepos.x * 8) + Selected_Character->tilepos.y * 8;
				Selected_Character->pos.x -= speed*dt;
				Selected_Character->pos.y += speed*dt;
			}
		}
		
		else if (d_l_d == TILE_COL_ID) {
			if ((p_y + 8) / 8 == t_y && (p_x ) / 8 == t_x) {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x -= speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
			}
		}
		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_x - 1) / 8 == t_x) {
				Selected_Character->pos.x -= speed*dt;
			}
		}
		if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((p_y + 8) / 8 == t_y) {
				Selected_Character->pos.y += speed*dt;
			}
		}
		break;

	case right_down:
		if (adjacent.down.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((p_y + 8) / 8 == t_y && (p_x + 8) / 8 == t_x) {
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
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID && d_r_d != TILE_COL_ID) {
			if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				Selected_Character->pos.x += speed*dt;
			}
			else if ((p_x  - t_x * 8) > (p_y - t_y * 8)) {
				Selected_Character->pos.y += speed*dt;
			}
			else {
				
				Selected_Character->pos.x += speed*dt;
				Selected_Character->pos.y += speed*dt;
			}
		}
		
		else if (d_r_d == TILE_COL_ID) {
			if ((p_y + 8) / 8 == t_y && (p_x + 8) / 8 == t_x) {
				Selected_Character->pos.y += speed*dt;
				Selected_Character->pos.x += speed*dt;
			}
			else {
				Selected_Character->pos.y += speed*dt;
			}
		}
		if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((p_x + 8) / 8 == t_x) {
				Selected_Character->pos.x += speed*dt;
			}
		}
		if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((p_y + 8) / 8 == t_y) {
				Selected_Character->pos.y += speed*dt;
			}
		}
	

		break;
	}






}

