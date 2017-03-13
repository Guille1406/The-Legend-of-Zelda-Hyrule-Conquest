#include "j1Player.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "p2Log.h"
#include "Character.h"


#define TILE_COL_ID 237

void Character::Move( float dt)
{

	uint x, y;
	App->win->GetWindowSize(x, y);


	// SHORT VARIABLES
	int pos_x = this->pos.x;
	int pos_y = this->pos.y;

	this->tilepos.x = (this->pos.x + 4) / 8;
	this->tilepos.y = (this->pos.y + 4) / 8;

	int tile_pos_x = this->tilepos.x;
	int tile_pos_y = this->tilepos.y;

	
	


	////Camera
	int movementx = pos_x * App->win->GetScale() + x / 2 - 8;
	int movementy = pos_y * App->win->GetScale() + y / 2 - 8;

	App->render->camera.x = movementx;
	App->render->camera.y = movementy;
	if (App->render->camera.x >= 0) App->render->camera.x = 0;
	if (-App->render->camera.x >= App->map->data.width * App->map->data.tile_width - App->render->camera.w / App->win->GetScale()) {
		App->render->camera.x = -1 * (App->map->data.width * App->map->data.tile_width - App->render->camera.w / App->win->GetScale());
	}

	if (App->render->camera.y >= 0) App->render->camera.y = 0;
	if (-App->render->camera.y >= App->map->data.height * App->map->data.tile_height - App->render->camera.h / App->win->GetScale()) {
		App->render->camera.y = -1 * (App->map->data.height * App->map->data.tile_height - App->render->camera.h / App->win->GetScale());
	}
	

	
	

	//DIAGONAL TILES
	uint diagonal_right_up = App->map->Colision->Get(tile_pos_x + 2, tile_pos_y -1);
	uint diagonal_left_up  = App->map->Colision->Get(tile_pos_x -1, tile_pos_y - 1);
	uint diagonal_right_down = App->map->Colision->Get(tile_pos_x +2, tile_pos_y +2);
	uint diagonal_left_down = App->map->Colision->Get(tile_pos_x -1, tile_pos_y +2);
	
	
	/////
	float speed = 1/dt;
	
	switch (movement_direction) {
	case move_up:
		
		if (adjacent.up.i != TILE_COL_ID && adjacent.up.j != TILE_COL_ID) {
			pos_y -= speed*dt;
			if (adjacent.left.j == TILE_COL_ID && pos_x< tile_pos_x*8) {
				pos_x += speed*dt;
			}
			if (adjacent.right.i == TILE_COL_ID && pos_x > tile_pos_x  * 8) {
				pos_x -= speed*dt;
			}
		}
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j != TILE_COL_ID) {
			if (7 - (pos_x +8- tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_x += speed*dt;
			}
			else if (7 - (pos_x + 8 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_y -= speed*dt;;
			}
			else {
				pos_y -= speed*dt;
				pos_x += speed*dt;
			}
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if (pos_x - tile_pos_x * 8 > pos_y - tile_pos_y * 8) {
				pos_x -= speed*dt;
			}
			else if (pos_x - tile_pos_x * 8 < pos_y - tile_pos_y * 8) {
				pos_y -= speed*dt;;
			}
			else {
				pos_y -= speed*dt;
				pos_x -= speed*dt;
			}
		}
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y) {
				pos_y-= speed*dt;
			}
		}
		
		break;

	case  move_down:
		
		if (adjacent.down.i != TILE_COL_ID && adjacent.down.j != TILE_COL_ID) {
			pos_y += speed*dt;
			if (adjacent.left.i == TILE_COL_ID && pos_x < tile_pos_x * 8) {
				pos_x += speed*dt;
			}
			if (adjacent.right.j == TILE_COL_ID && pos_x > tile_pos_x * 8) {
				pos_x -= speed*dt;
			}
		}
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j != TILE_COL_ID) {
			if (7 - (pos_x+8 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_x -= speed*dt;
			}
			else if (7 - (pos_x+8 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_y += speed*dt;
			}
			else {
				pos_y += speed*dt;
				pos_x -= speed*dt;
			}
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_y += speed*dt;
			}
			else if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_x += speed*dt;
			}
			else {
				pos_y += speed*dt;
				pos_x += speed*dt;
			}
		}
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_y + 8)  / 8 == tile_pos_y ) {
				pos_y += speed*dt;
			}
		}
		

		break;

	case move_left:
		if (adjacent.left.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID)
		{
			pos_x -= speed*dt;
			if (adjacent.up.i == TILE_COL_ID && pos_y< tile_pos_y * 8) {
				pos_y += speed*dt;
			}
			if (adjacent.down.j == TILE_COL_ID && pos_y > tile_pos_y * 8) {
				pos_y -= speed*dt;
			}
		}
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_x -= speed*dt;
			}
			else if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_y -= speed*dt;
			}
			else {
				pos_x -= speed*dt;
				pos_y -= speed*dt;
			}
		}
		else if (adjacent.left.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {

			if (7 - (pos_x + 8 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_y += speed*dt;
			}
			else if (7 - (pos_x +8 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_x -= speed*dt;
			}
			else {
				pos_y += speed*dt;
				pos_x -= speed*dt;
			}
		}
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_x - 1) / 8 == tile_pos_x) {
				pos_x -= speed*dt;
			}
		}
		break;
	case move_right:
		if (adjacent.right.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID)
		{
			pos_x += speed*dt;
			if (adjacent.up.j == TILE_COL_ID && pos_y< tile_pos_y * 8) {
				pos_y += speed*dt;
			}
			if (adjacent.down.i == TILE_COL_ID && pos_y > tile_pos_y * 8) {
				pos_y -= speed*dt;
			}
		}
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_y += speed*dt;
			}
			else if ((pos_x  - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_x += speed*dt;
			}
			else {
				pos_y += speed*dt;
				pos_x += speed*dt;
			}
		}
		else if (adjacent.right.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if (7 - (pos_x + 8 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_x += speed*dt;
			}
			else if (7 - (pos_x + 8 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_y -= speed*dt;
			}
			else {
				pos_y -= speed*dt;
				pos_x += speed*dt;
			}
		}
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((pos_x +8) / 8 == tile_pos_x ) {
				pos_x += speed*dt;
			}
		}
		break;

	case move_up_left:
		if (adjacent.up.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y && (pos_x - 1) / 8 == tile_pos_x) {
				pos_y -= speed*dt;
				pos_x -= speed*dt;
			}
		}

		else if (adjacent.up.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			pos_x -= speed*dt;
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			pos_y -= speed*dt;
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID && diagonal_left_up != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_x -= speed*dt;
			}
			else if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_y -= speed*dt;
			}
			else {

				pos_y = pos_x - tile_pos_x * 8 + tile_pos_y * 8;
				pos_x -= speed*dt;
				pos_y -= speed*dt;
			}
		}
		
		else if (diagonal_left_up == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y && (pos_x - 1) / 8 == tile_pos_x) {
				pos_y -= speed*dt;
				pos_x -= speed*dt;
			}
			else {
				pos_y -= speed*dt;
			}
		}

		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_x - 1) / 8 == tile_pos_x) {
				pos_x -= speed*dt;
			}
		}
		if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((pos_y - 1) / 8 == tile_pos_y) {
				pos_y -= speed*dt;
			}
		}
		break;

	case move_up_right:
		if (adjacent.up.j == TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			if ((pos_y) / 8 == tile_pos_y && (pos_x + 8) / 8 == tile_pos_x) {
				pos_y -= speed*dt;
				pos_x += speed*dt;
			}
		}

		else if (adjacent.up.j == TILE_COL_ID && adjacent.right.i != TILE_COL_ID) {
			pos_x += speed*dt;
		}
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			pos_y -= speed*dt;
		}
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i != TILE_COL_ID && diagonal_right_up != TILE_COL_ID) {
			if (7 - (pos_x+ 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_x += speed*dt;
			}
			else if (7 - (pos_x+6 - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_y -= speed*dt;
			}
			else {
			
				pos_x += speed*dt;
				pos_y -= speed*dt;
			}
		}
		
		 else if (diagonal_right_up == TILE_COL_ID) {
			if ((pos_y ) / 8 == tile_pos_y && (pos_x +8) / 8 == tile_pos_x) {
				pos_y -= speed*dt;
				pos_x += speed*dt;
			}
			else {
				pos_y -= speed*dt;
			}
		}

			if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			 if ((pos_x + 8) / 8 == tile_pos_x) {
				 pos_x += speed*dt;
			 }
		 }
			if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			 if ((pos_y - 1) / 8 == tile_pos_y) {
				 pos_y -= speed*dt;
			 }
		 }
		break;
	case move_down_left:

		if (adjacent.down.j == TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x) / 8 == tile_pos_x) {
				pos_y += speed*dt;
				pos_x -= speed*dt;
			}
		}

		else if (adjacent.down.j == TILE_COL_ID && adjacent.left.i != TILE_COL_ID) {
			pos_x -= speed*dt;
			
		}
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			pos_y += speed*dt;
			
		}
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i != TILE_COL_ID && diagonal_left_down != TILE_COL_ID) {
			if (7 - (pos_x + 6 - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_y += speed*dt;
			}
			else if (7 - (pos_x + 6- tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_x -= speed*dt;
			}
			else {
				pos_x -= speed*dt;
				pos_y += speed*dt;
			}
		}
		
		else if (diagonal_left_down == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x ) / 8 == tile_pos_x) {
				pos_y += speed*dt;
				pos_x -= speed*dt;
			}
			else {
				pos_y += speed*dt;
			}
		}
		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((pos_x - 1) / 8 == tile_pos_x) {
				pos_x -= speed*dt;
			}
		}
		if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y) {
				pos_y += speed*dt;
			}
		}
		break;

	case move_down_right:
		if (adjacent.down.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x + 8) / 8 == tile_pos_x) {
				pos_y += speed*dt;
				pos_x += speed*dt;
			}
		}

		else if (adjacent.down.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			pos_x += speed*dt;
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			pos_y += speed*dt;
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID && diagonal_right_down != TILE_COL_ID) {
			if ((pos_x - tile_pos_x * 8) < (pos_y - tile_pos_y * 8)) {
				pos_x += speed*dt;
			}
			else if ((pos_x  - tile_pos_x * 8) > (pos_y - tile_pos_y * 8)) {
				pos_y += speed*dt;
			}
			else {
				
				pos_x += speed*dt;
				pos_y += speed*dt;
			}
		}
		
		else if (diagonal_right_down == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y && (pos_x + 8) / 8 == tile_pos_x) {
				pos_y += speed*dt;
				pos_x += speed*dt;
			}
			else {
				pos_y += speed*dt;
			}
		}
		if (adjacent.right.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if ((pos_x + 8) / 8 == tile_pos_x) {
				pos_x += speed*dt;
			}
		}
		if (adjacent.down.i == TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((pos_y + 8) / 8 == tile_pos_y) {
				pos_y += speed*dt;
			}
		}
	
		break;
	}

	
		this->pos.x = pos_x; this->pos.y = pos_y;
		this->tilepos.x = tile_pos_x; this->tilepos.y = tile_pos_y;
	
}

