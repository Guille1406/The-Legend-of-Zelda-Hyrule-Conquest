#include "P_Zelda.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"
#include "Character.h"
#include "j1InputManager.h"

#define JUMP_DISTANCE 112



void P_Zelda::Attack(float dt)
{

		switch (character_direction) {
		case up:
			CreateArrow({ pos.x + 4,pos.y - 16,8,16 });
			break;
		case down:
			CreateArrow({ pos.x + 4,pos.y + 16,8,16 });
			break;
		case left:
			CreateArrow({ pos.x - 16,pos.y + 4,16,8 });
			break;
		case right:
			CreateArrow({ pos.x + 16,pos.y + 4,16,8 });
			break;
		}

		actual_event = idle;
		doing_script = false;
		
	
}

void P_Zelda::CreateArrow(SDL_Rect rect)
{
	Arrow* temp_arrow = new Arrow();	

	temp_arrow->collider = App->collision->AddCollider(rect, collider_arrow, App->player->Zelda, App->player);
	temp_arrow->collider->rect = rect;
	temp_arrow->pos.x = rect.x;
	temp_arrow->pos.y = rect.y;
	temp_arrow->direction = character_direction;
	temp_arrow->timer = SDL_GetTicks();
	Vec_Arrow->push_back(temp_arrow);

}

void P_Zelda::UpdateArrows()
{
	int arrow_speed = 10;
	for (int i = 0; i < Vec_Arrow->size(); i++) {
		switch (Vec_Arrow[0][i]->direction) {
		case up:
			Vec_Arrow[0][i]->pos.y -= arrow_speed;
			break;
		case down:
			Vec_Arrow[0][i]->pos.y  += arrow_speed;
			break;
		case left:
			Vec_Arrow[0][i]->pos.x -= arrow_speed;
			break;
		case right:
			Vec_Arrow[0][i]->pos.x += arrow_speed;
			break;
			
		}
		Vec_Arrow[0][i]->collider->SetPos(Vec_Arrow[0][i]->pos.x, Vec_Arrow[0][i]->pos.y, App->player->Zelda->GetLogicHeightPlayer());

		if (SDL_GetTicks() - Vec_Arrow[0][i]->timer > 1000) {
			Vec_Arrow[0][i]->collider->to_delete = true;
			Vec_Arrow->erase(Vec_Arrow->begin() + i);
			i--;
		}
	}

}



void P_Zelda::ThrowFunction(float dt, int &pos, bool add, bool is_horitzontal)
{
	static int final_pos = 0;
	int temp_pos = pos;
	static bool can_pass_wall = true;
	static bool zelda_collides = false;

	bool is_on_collision = false;
	int count = 1;
	if (GetLogicHeightPlayer() == 2) {
		count = 1;
	}
	
	int i = 1;
	if (!add)
		i = -1;

	bool stop_jumping = false;
	iPoint temp_point = tilepos;
	iPoint next_point = tilepos;

	static int before_wall_pos = 0;

	if (!temp) {
		zelda_collides = false;
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
				if (GetLogicHeightPlayer() == 2)
					count = 2;
				zelda_collides = true;
							
			}
			else if (GetLogic(count, temp_point) != TILE_COL_ID) {
				is_on_collision = false;
			}
			
			
			temp_pos = temp_pos + (i * 4);
			temp_point.x = (temp_pos / 16) * is_horitzontal + temp_point.x * !is_horitzontal;
			temp_point.y = (temp_pos / 16) * !is_horitzontal + temp_point.y * is_horitzontal;
			
		}

		

		int decrease = 1;
		if (!can_pass_wall || !zelda_collides) {
			can_pass_wall = true;

			ChangeLogicHeightPlayer(GetLogicHeightPlayer() - decrease);
		}
		else {
			if (GetLogicHeightPlayer() == 2 && zelda_collides) {
				decrease = 2;
				ChangeLogicHeightPlayer(GetLogicHeightPlayer() - decrease);
			}
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

		static direction aim_direction = down;
		//FIRST THINGS FIRST
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
			aim_direction = character_direction;
		}
		

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
			if (is_picked) {
				static bool can_throw = false;
				actual_event = pick;
				ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
				pos = App->player->Link->pos;
				if (((App->inputM->EventPressed(INPUTEVENT::PICK, 1) == EVENTSTATE::E_DOWN) && can_throw) || ((App->inputM->EventPressed(INPUTEVENT::PICK, 0) == EVENTSTATE::E_DOWN) && can_throw)) {
					actual_event = throw_;
					doing_script = true;
					is_picked = false;
					App->player->Link->im_lifting = false;
					can_throw = false;

				}
				else can_throw = true;
			}

			if (App->inputM->EventPressed(INPUTEVENT::JUMP, 0) == EVENTSTATE::E_DOWN  && !is_picked) {
				actual_event = roll;
				doing_script = true;
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
				if  (((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) && can_throw)|| ((App->inputM->EventPressed(INPUTEVENT::PICK, 0) == EVENTSTATE::E_DOWN) && can_throw)) {
					actual_event = throw_;
					doing_script = true;
					is_picked = false;
					App->player->Link->im_lifting = false;
					can_throw = false;
					
				}
				else can_throw = true;
			}

			 if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN && !is_picked) {
				actual_event = roll;
				doing_script = true;
			}
			 if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT) {
				 character_direction = aim_direction;
			 }
			 if (App->input->GetKey(SDL_SCANCODE_T) == KEY_UP ) {
				 actual_event = attack;
				 doing_script = true;
				 character_direction = aim_direction;
			 }

			return actual_event;
		}
	
}
