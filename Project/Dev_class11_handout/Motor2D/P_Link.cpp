#include "P_Link.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"
#include "j1InputManager.h"
#include"j1Audio.h"
#include"j1Render.h"
#include"Color.h"
void P_Link::Attack(float dt)
{
	//update
	if (attack_timer.Read() > 500) {
		attack_timer.Start();
		doing_script = false;

	}
	
}


void P_Link::link_sword_collider_update() {
	if (Link_sword->collider!=nullptr) {
		Link_sword->collider->to_delete = true;
	}
}

void P_Link::Orientation_collider_link_sword()
{	
	
	switch (character_direction) {
	case direction::up:
		//15,30 colliders
		Link_sword->Attack_range = { collision->rect.x,collision->rect.y - collision->rect.h,20,30 };
		break;
	case direction::down:
		Link_sword->Attack_range = { collision->rect.x,collision->rect.y+ collision->rect.h,20,30 };
		break;
	case direction::left:
		Link_sword->Attack_range = { collision->rect.x - collision->rect.w,collision->rect.y,30,20 };
		break;
	case direction::right:
		Link_sword->Attack_range = { collision->rect.x + collision->rect.w,collision->rect.y,30,20 };
		break;

	}
	Link_sword->collider = App->collision->AddCollider(Link_sword->Attack_range, COLLIDER_TYPE::collider_link_sword, Link_sword, App->player);
	
}



player_event P_Link::GetEvent()
{

	if (doing_script == false) {
		

		//EVENTS FOR GAMEPAD
		if (App->input->NumberOfGamePads() >= 1) {

			//MOVEMENT UP//
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
			//MOVEMENT DOWM//
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
			//MOVEMENT RIGHT//
			else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 1) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_right;
				character_direction = right;
				actual_event = move;
			}
			//MOVEMENT LEFT//
			else if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 1) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_left;
				character_direction = left;
				actual_event = move;
			}
			//IDDLE//
			else {
				movement_direction = move_idle;
				actual_event = idle;
			}
			//JUMP//
			if (can_jump) {
				actual_event = jump;
				doing_script = true;
				LOG("I'm Jumping :DDDD");
				can_jump = false;
			}

			//PICK ZELDA//
			 if (can_pick_up && !App->player->Zelda->doing_script) {
				if (App->inputM->EventPressed(INPUTEVENT::PICK, 1) == EVENTSTATE::E_REPEAT) {
					App->player->Zelda->is_picked = true;
					App->player->Zelda->ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
					actual_event = pick;
					im_lifting = true;
					can_pick_up = false;
				}			

			}
			 //TUMBLE//
			if (App->inputM->EventPressed(INPUTEVENT::JUMP, 1) == EVENTSTATE::E_DOWN && !im_lifting) {
				actual_event = roll;
				doing_script = true;
			}

			//ATTACK//
			if (App->inputM->EventPressed(INPUTEVENT::ATTACK, 1) == EVENTSTATE::E_DOWN && !im_lifting) {
				attack_timer.Start();
				App->audio->PlayFx(Link_Sword_Audio);
				//orientation collider link sword
				Orientation_collider_link_sword();
				actual_event = attack;
				doing_script = true;
				LOG("I'm Attacking :DDDD");
			}

			


		}

		else {
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
		
			else {
				movement_direction = move_idle;
				actual_event = idle;
			}
			 if (im_lifting) {
					actual_event = lifting;
					can_pick_up = false;
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
				App->audio->PlayFx(Link_Sword_Audio);
				//orientation collider link sword
				Orientation_collider_link_sword();
				actual_event = attack;
				doing_script = true;
				LOG("I'm Attacking :DDDD");
			}

			if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && !im_lifting) {
				actual_event = roll;
				doing_script = true;
			}

		}


		App->player->Link->can_pick_up = false;
		return actual_event;
	}
}


bool P_Link::Compare_Link_Sword_Collision(Enemy* enemy)
{
	bool ret = false;
	
	switch (enemy->Enemy_Orientation) {

	case OrientationEnemy::up_enemy:

		if (character_direction == direction::down)
			ret = true;

		break;
	case OrientationEnemy::down_enemy:
		
		if (character_direction == direction::up)
			ret = true;

		break;
	case OrientationEnemy::right_enemy:

		if (character_direction == direction::left)
			ret = true;

		break;
	case OrientationEnemy::left_enemy:

		if (character_direction == direction::right)
			ret = true;

		break;
		

	}






	return ret;
}

