#include "P_Zelda.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"

void P_Zelda::Attack()
{

}





player_event P_Zelda::GetEvent()
{
	SDL_Scancode UP;
	SDL_Scancode DOWN;
	SDL_Scancode LEFT;
	SDL_Scancode RIGHT;

	//Change the actual event, direction and move_direction depending ont he key pressed

	if (App->player->cooperative == false) {
		UP = SDL_SCANCODE_W;
		DOWN = SDL_SCANCODE_S;
		LEFT = SDL_SCANCODE_A;
		RIGHT = SDL_SCANCODE_D;

	}
	else {
		UP = SDL_SCANCODE_UP;
		DOWN = SDL_SCANCODE_DOWN;
		LEFT = SDL_SCANCODE_LEFT;
		RIGHT = SDL_SCANCODE_RIGHT;

	}
	if (doing_script == false) {
		if (App->input->GetKey(UP) == KEY_REPEAT) {
			if (App->input->GetKey(LEFT) == KEY_REPEAT) {
				movement_direction = move_up_left;
			}
			else if (App->input->GetKey(RIGHT) == KEY_REPEAT) {
				movement_direction = move_up_right;
			}
			else {
				movement_direction = move_up;

			}
			character_direction = up;
			actual_event = move;
		}


		else if (App->input->GetKey(DOWN) == KEY_REPEAT) {
			if (App->input->GetKey(LEFT) == KEY_REPEAT) {
				movement_direction = move_down_left;
			}
			else if (App->input->GetKey(RIGHT) == KEY_REPEAT) {
				movement_direction = move_down_right;
			}
			else {
				movement_direction = move_down;

			}
			character_direction = down;
			actual_event = move;
		}


		else if (App->input->GetKey(RIGHT) == KEY_REPEAT) {
			movement_direction = move_right;
			character_direction = right;
			actual_event = move;
		}

		else if (App->input->GetKey(LEFT) == KEY_REPEAT) {
			movement_direction = move_left;
			character_direction = left;
			actual_event = move;
		}



		else {
			movement_direction = move_idle;
			actual_event = idle;
		}

		if (can_jump) {
			actual_event = jump;
			doing_script = true;
			LOG("I'm Jumping :DDDD");
			can_jump = false;
		}


		if (is_picked) {
			static bool can_throw = false;
			actual_event = pick;
			pos = App->player->Link->pos;
			if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && can_throw) {
				actual_event = jump;
				doing_script = true;
				is_picked = false;
				App->player->Link->im_lifting = false;
				can_throw = false;
			}
			else can_throw = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {
			actual_event = roll;
			doing_script = true;
		}

		return actual_event;
	}
}
