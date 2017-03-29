#include "P_Link.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"
#include "j1InputManager.h"
#include"j1Render.h"
#include"Color.h"
void P_Link::Attack(float dt)
{
	if (attack_timer.Read()<500) {

		actual_event = attack;
		this->doing_script = true;
		switch (this->character_direction) {
		case direction::right:
		{
			SDL_Rect Attack_range = { front_collider->rect.x+10,front_collider->rect.y+10,30,30 };



			attack_collider->rect = Attack_range;
			//App->render->DrawQuad(Attack_range, Blue(0), Blue(1), Blue(2), 255, true, true);
			break;
		}
		case direction::left:

			break;
		case direction::up:

			break;
		case direction::down:

			break;



		}
	}
	else {
		attack_timer.Start();
		doing_script = false;
	}
}




player_event P_Link::GetEvent()
{

	if (doing_script == false) {
		

			if (App->inputM->EventPressed(INPUTEVENT::MUP, 1) == EVENTSTATE::E_REPEAT) {
				if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 1) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_up_right;
				}
				else if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 1) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_up_left;
				}
				else {
					movement_direction = move_up;

				}
				character_direction = up;
				actual_event = move;
			}

			else if (App->inputM->EventPressed(INPUTEVENT::MDOWN, 1) == EVENTSTATE::E_REPEAT) {
				if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 1) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_down_left;
				}
				else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 1) == EVENTSTATE::E_REPEAT) {
					movement_direction = move_down_right;
				}
				else {
					movement_direction = move_down;

				}
				character_direction = down;
				actual_event = move;
			}

			else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 1) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_right;
				character_direction = right;
				actual_event = move;
			}
			else if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 1) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_left;
				character_direction = left;
				actual_event = move;
			}
			else if (can_pick_up && !App->player->Zelda->doing_script) {
				if (App->inputM->EventPressed(INPUTEVENT::PICK, 1) == EVENTSTATE::E_REPEAT) {
					App->player->Zelda->is_picked = true;
					App->player->Zelda->ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
					actual_event = pick;
					im_lifting = true;
					can_pick_up = false;
				}

			}
			if (App->inputM->EventPressed(INPUTEVENT::JUMP, 1) == EVENTSTATE::E_DOWN && !im_lifting) {
				actual_event = roll;
				doing_script = true;
			}

		


			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
				if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
					movement_direction = move_up_right;
				}
				else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
					movement_direction = move_up_left;
				}
				else {
					movement_direction = move_up;

				}
				character_direction = up;
				actual_event = move;
			}

			else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
					movement_direction = move_down_left;
				}
				else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
					movement_direction = move_down_right;
				}
				else {
					movement_direction = move_down;

				}
				character_direction = down;
				actual_event = move;
			}

			else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

				movement_direction = move_right;
				character_direction = right;
				actual_event = move;
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

				movement_direction = move_left;
				character_direction = left;
				actual_event = move;
			}
			else if (im_lifting) {
				actual_event = lifting;
				can_pick_up = false;
			}

			else {
				movement_direction = move_idle;
				actual_event = idle;
			}

			if (can_pick_up && !App->player->Zelda->doing_script) {
				if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
					App->player->Zelda->is_picked = true;
					App->player->Zelda->ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
					actual_event = pick;
					im_lifting = true;
					can_pick_up = false;
				}

			}

			if (can_jump) {
				actual_event = jump;
				doing_script = true;
				LOG("I'm Jumping :DDDD");
				can_jump = false;
			}

			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
				attack_timer.Start();
				actual_event = attack;
				doing_script = true;
				LOG("I'm Attacking :DDDD");
			}
			
			if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN  && !im_lifting) {
				actual_event = roll;
				doing_script = true;
			}

		
		
		
		App->player->Link->can_pick_up = false;
		return actual_event;
	}
}