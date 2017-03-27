#include "P_Zelda.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"
#include "Character.h"
#include "j1InputManager.h"
#define JUMP_DISTANCE 112

void P_Zelda::Attack()
{

}

void P_Zelda::ThrowFunction(float dt, int &pos, bool add, bool is_horitzontal)
{
	static int final_pos = 0;
	int temp_pos = pos;
	bool can_pass_wall = true;
	bool is_on_collision = false;
	bool count = true;
	int i = 1;
	if (!add)
		i = -1;

	bool stop_jumping = false;
	iPoint temp_point = tilepos;
	iPoint next_point = tilepos;

	static int before_wall_pos = 0;

	if (!temp) {
		final_pos = pos + (i * JUMP_DISTANCE);
		before_wall_pos = final_pos;

		while ((i * temp_pos < i*final_pos)) {

			next_point.x = temp_point.x + is_horitzontal * i;
			next_point.y = temp_point.y + !is_horitzontal * i;

			if (GetLogic(count, temp_point) == TILE_COL_ID && !is_on_collision) {
				is_on_collision = true;
				before_wall_pos = temp_pos;
				if (GetLogic(count, next_point) == TILE_COL_ID)
					break;
				if (!can_pass_wall) {
					before_wall_pos = temp_pos + i * 64;
				}
				can_pass_wall = !can_pass_wall;
				count = false;
							
			}
			else if (GetLogic(count, temp_point) != TILE_COL_ID) {
				is_on_collision = false;
			}
			
			
			temp_pos = temp_pos + (i * 4);
			temp_point.x = (temp_pos / 16) * is_horitzontal + temp_point.x * !is_horitzontal;
			temp_point.y = (temp_pos / 16) * !is_horitzontal + temp_point.y * is_horitzontal;
			
		}
	}

	temp = true;


	if ((i * pos < i*before_wall_pos)) {
		pos = pos + (i * 4);
	}
	// if player reached the final pos, player height decreases 1
	else {
		temp = false;
		doing_script = false;
		
		if (!can_pass_wall) {
			int decrease = 1;
			if (GetLogicHeightPlayer() == 3)
				decrease = 2;
			ChangeLogicHeightPlayer(GetLogicHeightPlayer() - 1);
		}
	}
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

		if (doing_script == false) {

			if (App->inputM->EventPressed(INPUTEVENT::MUP, 0) == EVENTSTATE::E_REPEAT) {
				if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 0) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_up_right;
				}
				else if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 0) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_up_left;
				}
				else {
					movement_direction = move_up;

				}
				character_direction = up;
				actual_event = move;
			}

			else if (App->inputM->EventPressed(INPUTEVENT::MDOWN, 0) == EVENTSTATE::E_REPEAT) {
				if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 0) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_down_left;
				}
				else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 0) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_down_right;
				}
				else {
					movement_direction = move_down;

				}
				character_direction = down;
				actual_event = move;
			}

			else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 0) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_right;
				character_direction = right;
				actual_event = move;
			}
			else if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 0) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_left;
				character_direction = left;
				actual_event = move;
			}


			else if (App->input->GetKey(UP) == KEY_REPEAT) {
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
				ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
				pos = App->player->Link->pos;
				if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && can_throw) {
					actual_event = throw_;
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
}
