#include "P_Zelda.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "j1Player.h"
#include "Character.h"
#include "j1InputManager.h"
#include "j1Player.h"
#include "j1Render.h"
#include"j1Audio.h"

#define JUMP_DISTANCE 128

void P_Zelda::Attack(float dt)
{
	if (!temp) {
		temp = true;
	
			switch (character_direction) {
			case up:
				CreateArrow({ pos.x + 4,pos.y ,8,16 });
				break;
			case down:
				CreateArrow({ pos.x + 16,pos.y ,8,16 });
				break;
			case left:
				CreateArrow({ pos.x,pos.y -4,16,8 });
				break;
			case right:
				CreateArrow({ pos.x,pos.y - 4,16,8 });
				break;
			}
		}
	
		//actual_event = idle;
		//doing_script = false;
		//update
		if (attack_timer.Read() > 300) {
			attack_timer.Start();
			doing_script = false;
			temp = false;
		}
}

void P_Zelda::CreateArrow(SDL_Rect rect)
{
	Arrow* temp_arrow = new Arrow();	

	temp_arrow->collider = App->collision->AddCollider(rect, collider_arrow, temp_arrow, App->player);
	temp_arrow->collider->rect = rect;
	temp_arrow->pos.x = rect.x;
	temp_arrow->pos.y = rect.y;
	temp_arrow->max_distance = 300;
	temp_arrow->direction = (arrow_direction)character_direction;
	temp_arrow->timer = SDL_GetTicks();
	temp_arrow->logic_height = App->player->Zelda->GetLogicHeightPlayer();
	//temp_arrow->can_move = false;
	
	switch (temp_arrow->direction) {
	case arrow_up:
		temp_arrow->arrow_rect = rect_arrow_up;
		break;

	case arrow_down:
		temp_arrow->arrow_rect = rect_arrow_down;
		break;

	case arrow_left:
		temp_arrow->arrow_rect = rect_arrow_left;
		break;

	case arrow_right:
		temp_arrow->arrow_rect = rect_arrow_right;
		break;
	}

	Vec_Arrow.push_back(temp_arrow);
}

void P_Zelda::UpdateArrows()
{
	int arrow_speed = 10;
	for (uint i = 0; i < Vec_Arrow.size(); i++) {
		
		if (Vec_Arrow[i]->can_move) {
		Vec_Arrow[i]->Check_Wall();
		Vec_Arrow[i]->collider->SetPos(Vec_Arrow[i]->pos.x, Vec_Arrow[i]->pos.y, App->player->Zelda->GetLogicHeightPlayer());
		}
		else {
			if (Vec_Arrow[i]->is_attached) {
				Vec_Arrow[i]->pos.x = Vec_Arrow[i]->attached_enemy->pos.x + Vec_Arrow[i]->offset.x;
				Vec_Arrow[i]->pos.y = Vec_Arrow[i]->attached_enemy->pos.y + Vec_Arrow[i]->offset.y;
				Vec_Arrow[i]->collider->SetPos(Vec_Arrow[i]->pos.x, Vec_Arrow[i]->pos.y, App->player->Zelda->GetLogicHeightPlayer());
			}
		}
		App->render->Blit(Vec_Arrow[i]->entity_texture, Vec_Arrow[i]->pos.x, Vec_Arrow[i]->pos.y, &Vec_Arrow[i]->arrow_rect);

		if (SDL_GetTicks() - Vec_Arrow[i]->timer > 1000) {
			if(Vec_Arrow[i]->collider != nullptr && Vec_Arrow[i]->collider->type == collider_arrow)
			Vec_Arrow[i]->collider->to_delete = true;
			Vec_Arrow.erase(Vec_Arrow.begin() + i);
			i--;
		}
	}
}

void P_Zelda::ThrowFunction(float dt, int &pos, bool add, bool is_horitzontal)
{
	int final_pos = 0;
	int temp_pos = pos;
	bool can_pass_wall = true;
	bool zelda_collides = false;
	int decrease = 1;
	bool is_on_collision = false;
	int count = 1;
	if (GetLogicHeightPlayer() == 2) {
		count = 1;
	}
	bool stop = false;

	int n = 1;
	if (!add)
		n = -1;

	bool stop_jumping = false;
	iPoint temp_point = tilepos;
	iPoint next_point = tilepos;
	iPoint last_point = { 0,0 };
	static int before_wall_pos = 0;

	int max_collisions = 0;

	if (!temp) {
		
		zelda_collides = false;
		final_pos = pos + (n * JUMP_DISTANCE);
		before_wall_pos = final_pos;

		while ((n * temp_pos < n*final_pos)) {

			next_point.x = temp_point.x + is_horitzontal * n;
			next_point.y = temp_point.y + !is_horitzontal * n;

			uint i = 0;
			if (!is_on_collision ) {

				if (stop)break;
				for (i = 0; i <= GetLogicHeightPlayer() && i<3; i++) {
					if (GetLogic(i, temp_point) == App->map->CANT_PASS_COL_ID) {
						stop = true;
						before_wall_pos = temp_pos;
						//decrease = 1;
						break;
					}

					if (GetLogic(i, temp_point) != 0 && temp_point != last_point) {
						max_collisions++;
						if(max_collisions%2 ==0)
							before_wall_pos = temp_pos + n * 64;
						if (max_collisions % 2 == 1)
							before_wall_pos = temp_pos;
						
						decrease = i;
						

						last_point = temp_point;
						break;
						/*
						max_collisions++;
						is_on_collision = true;
						before_wall_pos = temp_pos;
						last_point = temp_point;

						if (!can_pass_wall) {
							before_wall_pos = temp_pos + n * 64;
						}
						can_pass_wall = !can_pass_wall;
						zelda_collides = true;
						decrease = i;

						break;*/
					}
				}
			}
			if (max_collisions > 4) {
				before_wall_pos = pos; decrease = 1;
			}
			if (GetLogic(decrease, temp_point) == 0  || temp_point != last_point) {
				is_on_collision = false;
			}
			temp_pos = temp_pos + (n * 1);
			temp_point.x = ((temp_pos) / 16) * is_horitzontal + temp_point.x * !is_horitzontal;
			temp_point.y = ((temp_pos) / 16) * !is_horitzontal + temp_point.y * is_horitzontal;
			if (stop)
				break;
		}
		ChangeLogicHeightPlayer(GetLogicHeightPlayer() - decrease);
	}

	temp = true;

	if ((n * pos < n*before_wall_pos)) {
		pos = pos + (n * 4);
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
	//can_fall = true;

	if (App->player->cooperative == false) {
		

	}
	else {
		UP = SDL_SCANCODE_UP;
		DOWN = SDL_SCANCODE_DOWN;
		LEFT = SDL_SCANCODE_LEFT;
		RIGHT = SDL_SCANCODE_RIGHT;
	}

	if (can_jump) {
		actual_event = jump;
		doing_script = true;

		can_jump = false;
	}

	if (actual_event == attack && is_picked == true) {
		pos = App->player->Link->pos;
	}

	if (doing_script == false) {

		static direction aim_direction = down;

		//EVENTS FOR GAMEPAD
		if (App->input->NumberOfGamePads() >= 2) {

			if (App->inputM->EventPressed(INPUTEVENT::ATTACK, 0) == EVENTSTATE::E_DOWN) {
				aim_direction = character_direction;
			}

			//MOVEMENT UP//
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
			//MOVEMENT DOWN//
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
			//MOVEMENT RIGHT//
			else if (App->inputM->EventPressed(INPUTEVENT::MRIGHT, 0) == EVENTSTATE::E_REPEAT) {

				movement_direction = move_right;
				character_direction = right;
				actual_event = move;
			}
			//MOVEMENT LEFT//
			else if (App->inputM->EventPressed(INPUTEVENT::MLEFT, 0) == EVENTSTATE::E_REPEAT) {

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

			//TUMBLE//
			if (App->inputM->EventPressed(INPUTEVENT::TUMBLE, 0) == EVENTSTATE::E_DOWN && !is_picked) {
				actual_event = roll;
				doing_script = true;
				is_rolling = true;
			}
			//PICKED UP//
			if (is_picked) {
				static bool can_throw = false;
				actual_event = pick;
				ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
				pos.x = App->player->Link->pos.x;
				pos.y = App->player->Link->pos.y;
				if (((App->inputM->EventPressed(INPUTEVENT::PICK, 1) == EVENTSTATE::E_DOWN) || (App->inputM->EventPressed(INPUTEVENT::PICK, 0) == EVENTSTATE::E_DOWN)) && can_throw) {
					if (!App->player->Link->doing_script) {
						App->audio->PlayFx(Throw_Audio);
						actual_event = throw_;
						doing_script = true;
						is_picked = false;
						App->player->Link->im_lifting = false;
						can_throw = false;
					}
				}
				else can_throw = true;
			}
			//ATTACK//
			if (App->inputM->EventPressed(INPUTEVENT::ATTACK, 0) == EVENTSTATE::E_DOWN && !doing_script) {
				attack_timer.Start();
				App->audio->PlayFx(Arrow_Audio);
				actual_event = attack;
				doing_script = true;
				character_direction = aim_direction;
				bow = 0;
			}
		}
		else
		{
			//FIRST THINGS FIRST

			if (App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) {

				aim_direction = character_direction;
			}

			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) {
				if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
					movement_direction = move_up_left;
				}
				else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
					movement_direction = move_up_right;
				}
				else {
					movement_direction = move_up;

				}
				character_direction = up;
				actual_event = move;
			}

			else if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) {
				if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
					movement_direction = move_down_left;
				}
				else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
					movement_direction = move_down_right;
				}
				else {
					movement_direction = move_down;
				}
				character_direction = down;
				actual_event = move;
			}

			else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
				movement_direction = move_right;
				character_direction = right;
				actual_event = move;
			}

			else if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
				movement_direction = move_left;
				character_direction = left;
				actual_event = move;
			}

			else {
				movement_direction = move_idle;
				actual_event = idle;
			}

			/*
			if (can_jump) {
			actual_event = jump;
			doing_script = true;
			LOG("I'm Jumping :DDDD");
			can_jump = false;
			}
			*/

			if (is_picked) {
				static bool can_throw = false;
				actual_event = pick;
				ChangeLogicHeightPlayer(App->player->Link->GetLogicHeightPlayer() + 1);
				pos = App->player->Link->pos;
				if (((App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) || App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) && can_throw && !App->player->Link->doing_script) {
					if (!App->player->Link->doing_script) {
						App->audio->PlayFx(Throw_Audio);
						actual_event = throw_;
						doing_script = true;
						is_picked = false;
						App->player->Link->im_lifting = false;
						can_throw = false;
					}
				}
				else can_throw = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN && !is_picked) {

				actual_event = roll;
				doing_script = true;
				is_rolling = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_REPEAT) {
				character_direction = aim_direction;
			}
			if (App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_UP) {
				if (!doing_script) {
				attack_timer.Start();
				App->audio->PlayFx(Arrow_Audio);
				actual_event = attack;
				doing_script = true;
				character_direction = aim_direction;
			}
			}
		}
	}
	return actual_event;
}

bool Arrow::Check_Wall()
{
	int temp_pos = 0;
	switch (direction) {
	case up: 
		Check_Wall_Loop(pos.y,false, false);
		break;
	case down:
		Check_Wall_Loop( pos.y, true, false);
		break;
	case left:
		Check_Wall_Loop(pos.x, false, true);
		break;
	case right: 
		Check_Wall_Loop(pos.x, true,true);
		break;
	}
	
	return false;
}

bool Arrow::Check_Wall_Loop(int & pos, bool add, bool is_horitzontal)
{
	iPoint temp_point;
	temp_point.x = (pos / 16)* is_horitzontal + (this->pos.x / 16) * !is_horitzontal;
	temp_point.y = (pos / 16) * !is_horitzontal + (this->pos.y / 16) * is_horitzontal;
	iPoint final_point = temp_point;

	int temp_pos = pos;
	int first_wall_pos;
	bool is_on_collision = false;
	bool is_second_wall = false;
	bool is_first_wall = true;
	bool stop = false;
	
	int i = 1;
	if (!add)
		i = -1;
	int first_height = 0;
	int second_height = 0;
	int height = 0;
	//static int final_pos = temp_pos + i * 200;
	if (!temp) {

		max_distance = temp_pos + i*1000;
		before_wall_pos = max_distance;
		first_wall_pos = max_distance;
		while (i * temp_pos < i * max_distance) {
			
			temp_point.x = (temp_pos / 16)* is_horitzontal + (this->pos.x / 16) * !is_horitzontal;
			temp_point.y = (temp_pos / 16) * !is_horitzontal + (this->pos.y / 16) * is_horitzontal;
			if (!is_on_collision) {
				for (int n = -1; n < 2; n++) {
					if (GetLogicArrow(n, temp_point) != NOT_COLISION_ID ) {
						before_wall_pos = temp_pos + i * 40;
						
						height = n;
						is_on_collision = true;
						if (is_second_wall && !is_first_wall) {
							second_height = n;
							stop = true;
						}
						if (is_first_wall) {
							first_height = n;
							is_first_wall = false;
							first_wall_pos = temp_pos + i * 40;
						}
					}
				}
			}
			if (stop == true)
				break;
			else {
				if (GetLogicArrow(height, temp_point) == NOT_COLISION_ID) {
					is_on_collision = false;
					is_second_wall = true;
					
					//is_first_wall = false;
				}
			}
			temp_pos += i*1;
		}
		if (second_height > first_height) {
			before_wall_pos = temp_pos + i * 1000;
		}
		else {
			before_wall_pos = first_wall_pos;
		}
	}
	
	temp = true;
	if (i*pos < i*before_wall_pos) {
		pos += 10 * i;
	}
	else {
		//arrow sound
		//App->audio->PlayFx(App->player->Zelda->Arrow_Hit_Wall_Audio);
		can_move = false;
		
	}
	return false;
}

int Arrow::GetLogicArrow(int minus_height, iPoint pos)
{
	std::vector<MapLayer*> vector = App->map->V_Colision;

	iPoint tile_pos;
	tile_pos.x = pos.x;
	tile_pos.y = pos.y;

	int i, j;
	int height = App->player->Zelda->GetLogicHeightPlayer();

	if (height - minus_height < 0) return 0;
	if (height - minus_height >=3) return 0;
	switch (direction)
	{
	case up:
		i = vector[height - minus_height]->Get(tile_pos.x, tile_pos.y - 1);
		j = vector[height - minus_height]->Get(tile_pos.x + 1, tile_pos.y - 1);
		break;
	case down:
		i = vector[height - minus_height]->Get(tile_pos.x, tile_pos.y + 2);
		j = vector[height - minus_height]->Get(tile_pos.x + 1, tile_pos.y + 2);
		break;
	case left:
		i = vector[height - minus_height]->Get(tile_pos.x - 1, tile_pos.y);
		j = vector[height - minus_height]->Get(tile_pos.x - 1, tile_pos.y + 1);
		break;
	case right:
		i = vector[height - minus_height]->Get(tile_pos.x + 2, tile_pos.y);
		j = vector[height - minus_height]->Get(tile_pos.x + 2, tile_pos.y + 1);
		break;
	}

	if (i != 0)
		return i;
	if (j != 0)
		return j;

	return 0;
}