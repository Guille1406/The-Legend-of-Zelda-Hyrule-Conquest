#include "j1Player.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"

#define TILE_COL_ID 237

void j1Player::Move()
{
	enum key_state {
		up,
		down,
		left,
		right,
		left_up,
		left_down,
		right_up,
		right_down,
		idle
	};

	key_state state = idle;
	// HAY QUE INTENTAR QUE ESTO NO SEA TAN HARD CODE
	//ADEMAS HAY ALGUNOS BUGS :S


	p2Point<int> pos = selected_character->pos;
	p2Point<int> o_pos = other_character->pos;

	selected_character->tilepos.x = pos.x / 8;
	selected_character->tilepos.y = pos.y / 8;

	other_character->tilepos.x = o_pos.x / 8;
	other_character->tilepos.y = o_pos.y / 8;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			state = left_up;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			state = right_up;
		}
		else {
			state = up;
		}
	}

	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			state = left_down;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			state = right_down;
		}
		else {
			state = down;
		}
	}

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {


		state = right;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

		state = left;
	}
	else state = idle;

	if (state == left_up) {
		int a = 0;
	}
	int t_x = selected_character->tilepos.x;
	int t_y = selected_character->tilepos.y;
	int p_x = selected_character->pos.x;
	int p_y = selected_character->pos.y;

	switch (state) {
	case up:
		if (adjacent.up.i != TILE_COL_ID && adjacent.up.j != TILE_COL_ID)
			selected_character->pos.y = pos.y - 1;
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j != TILE_COL_ID) {
			if (7 - (p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x++;
			}
			else if (7 - (p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y--;
			}
			else {
				//pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y - 1;
				selected_character->pos.x = pos.x + 1;
			}
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if (p_x - t_x * 8 > p_y - t_y * 8) {
				selected_character->pos.x--;
			}
			else if (p_x - t_x * 8 < p_y - t_y * 8) {
				selected_character->pos.y--;
			}
			else {
				//pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y - 1;
				selected_character->pos.x = pos.x - 1;
			}
		}
		else if (adjacent.up.i == TILE_COL_ID && adjacent.up.j == TILE_COL_ID) {
			if ((p_y - 1) / 8 == t_y) {
				selected_character->pos.y--;
			}
		}
		break;

	case down:
		if (adjacent.down.i != TILE_COL_ID && adjacent.down.j != TILE_COL_ID)
			selected_character->pos.y = pos.y + 1;
		else if (adjacent.down.i == TILE_COL_ID && adjacent.down.j != TILE_COL_ID) {
			if (7 - (p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x--;
			}
			else if (7 - (p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y++;
			}
			else {
				// pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y + 1;
				selected_character->pos.x = pos.x - 1;
			}
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.down.j == TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.y++;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.x++;
			}
			else {
				// pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y + 1;
				selected_character->pos.x = pos.x + 1;
			}
		}

		break;

	case left:
		if (adjacent.left.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID)
			selected_character->pos.x = pos.x - 1;
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x--;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y--;
			}
			else {
				//pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
				selected_character->pos.x = pos.x - 1;
				selected_character->pos.y = pos.y - 1;
			}
		}
		else if (adjacent.left.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {

			if (7 - (p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.y++;
			}
			else if (7 - (p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.x--;
			}
			else {
				// pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y + 1;
				selected_character->pos.x = pos.x - 1;
			}
		}
		else if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_x - 1) / 8 == t_x) {
				selected_character->pos.x--;
			}
		}
		break;
	case right:
		if (adjacent.right.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID)
			selected_character->pos.x = pos.x + 1;
		else if (adjacent.right.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.y++;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.x++;
			}
			else {
				//pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y + 1;
				selected_character->pos.x = pos.x + 1;
			}
		}
		else if (adjacent.right.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			if (7 - (p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x++;
			}
			else if (7 - (p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y--;
			}
			else {
				// pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
				selected_character->pos.y = pos.y - 1;
				selected_character->pos.x = pos.x + 1;
			}
		}

		break;

	case left_up:
		if (adjacent.up.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {

		}

		else if (adjacent.up.i == TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			selected_character->pos.x = pos.x - 1;
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			selected_character->pos.y = pos.y - 1;
		}
		else if (adjacent.up.i != TILE_COL_ID && adjacent.left.j != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x--;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y--;
			}
			else {

				pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
				selected_character->pos.x = pos.x - 1;
				selected_character->pos.y = pos.y - 1;
			}
		}
		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_x - 1) / 8 == t_x) {
				selected_character->pos.x--;
			}
		}
		break;

	case right_up:
		if (adjacent.up.j == TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {

		}

		else if (adjacent.up.j == TILE_COL_ID && adjacent.right.i != TILE_COL_ID) {
			selected_character->pos.x = pos.x + 1;
		}
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i == TILE_COL_ID) {
			selected_character->pos.y = pos.y - 1;
		}
		else if (adjacent.up.j != TILE_COL_ID && adjacent.right.i != TILE_COL_ID) {
			if (7 - (p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x++;
			}
			else if (7 - (p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y--;
			}
			else {
				//pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
				selected_character->pos.x = pos.x + 1;
				selected_character->pos.y = pos.y - 1;
			}
		}

		break;
	case left_down:

		if (adjacent.down.j == TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {

		}

		else if (adjacent.down.j == TILE_COL_ID && adjacent.left.i != TILE_COL_ID) {
			selected_character->pos.x = pos.x - 1;
		}
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i == TILE_COL_ID) {
			selected_character->pos.y = pos.y + 1;
		}
		else if (adjacent.down.j != TILE_COL_ID && adjacent.left.i != TILE_COL_ID) {
			if (7 - (p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.y++;
			}
			else if (7 - (p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.x--;
			}
			else {
				// pos.y = 7 - (pos.x - selected_character->tilepos.x * 8) + selected_character->tilepos.y * 8;
				selected_character->pos.x = pos.x - 1;
				selected_character->pos.y = pos.y + 1;
			}
		}
		if (adjacent.left.i == TILE_COL_ID && adjacent.left.j == TILE_COL_ID) {
			if ((p_x - 1) / 8 == t_x) {
				selected_character->pos.x--;
			}
		}
		break;

	case right_down:
		if (adjacent.down.i == TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {

		}

		else if (adjacent.down.i == TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			selected_character->pos.x = pos.x + 1;
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j == TILE_COL_ID) {
			selected_character->pos.y = pos.y + 1;
		}
		else if (adjacent.down.i != TILE_COL_ID && adjacent.right.j != TILE_COL_ID) {
			if ((p_x - t_x * 8) > (p_y - t_y * 8)) {
				selected_character->pos.x++;
			}
			else if ((p_x - t_x * 8) < (p_y - t_y * 8)) {
				selected_character->pos.y++;
			}
			else {
				//pos.y = pos.x - selected_character->tilepos.x * 8 + selected_character->tilepos.y * 8;
				selected_character->pos.x = pos.x + 1;
				selected_character->pos.y = pos.y + 1;
			}
		}

		break;
	}




	uint x, y;
	App->win->GetWindowSize(x, y);
	App->render->camera.x = -selected_character->pos.x * 3 + x / 2 - 8;
	App->render->camera.y = -selected_character->pos.y * 3 + y / 2 - 8;

}