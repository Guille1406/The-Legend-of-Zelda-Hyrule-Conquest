#include "Boss.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Object.h"

Legs::Legs(const Legs& obj) {
	
	
	
	parent_boss = obj.parent_boss;
	Foot temp_foot;
	temp_foot.parent_boss = parent_boss;

	temp_foot.parent_offset = { 50,30 };
	temp_foot.pos = { parent_boss->centre_pos.x - 200, parent_boss->centre_pos.y  };
	temp_foot.pivot_point = { parent_boss->pos.x + temp_foot.parent_offset.x, parent_boss->pos.y + temp_foot.parent_offset.y };
	temp_foot.max_point = { (int)(temp_foot.pos.x - (float)(temp_foot.pos.x - temp_foot.pivot_point.x) / 1.5),temp_foot.pivot_point.y - 50 - abs(temp_foot.pos.y - temp_foot.pivot_point.y) };

	foot1 = new Foot(temp_foot);

	temp_foot.parent_offset = { 180,30};
	temp_foot.pos = { parent_boss->centre_pos.x + 200, parent_boss->centre_pos.y  };
	temp_foot.pivot_point = { parent_boss->pos.x + temp_foot.parent_offset.x, parent_boss->pos.y + temp_foot.parent_offset.y };
	temp_foot.max_point = { (int)(temp_foot.pos.x - (float)(temp_foot.pos.x - temp_foot.pivot_point.x) / 1.5),temp_foot.pivot_point.y - 50 - abs(temp_foot.pos.y - temp_foot.pivot_point.y) };

	foot2 = new Foot(temp_foot);	

	temp_foot.pos = { parent_boss->centre_pos.x - 200, parent_boss->centre_pos.y +150 };
	temp_foot.parent_offset = { 50,180};
	temp_foot.pivot_point = { parent_boss->pos.x + temp_foot.parent_offset.x, parent_boss->pos.y + temp_foot.parent_offset.y };
	temp_foot.max_point = { (int)(temp_foot.pos.x - (float)(temp_foot.pos.x - temp_foot.pivot_point.x) / 1.5),temp_foot.pivot_point.y - 50 - abs(temp_foot.pos.y - temp_foot.pivot_point.y) };

	foot3 = new Foot(temp_foot);	

	temp_foot.pos = { parent_boss->centre_pos.x +200, parent_boss->centre_pos.y +150 };
	temp_foot.parent_offset = { 180,180 };
	temp_foot.pivot_point = { parent_boss->pos.x + temp_foot.parent_offset.x, parent_boss->pos.y + temp_foot.parent_offset.y };
	temp_foot.max_point = { (int)(temp_foot.pos.x - (float)(temp_foot.pos.x - temp_foot.pivot_point.x) / 1.5),temp_foot.pivot_point.y - 50 - abs(temp_foot.pos.y - temp_foot.pivot_point.y) };

	foot4 = new Foot(temp_foot);

	
	
	
}

Legs::~Legs()
{
	
	
}

void Boss::Draw(int height)
{
	if(height == logic_height)
	App->render->Blit(boss_atlas, pos.x, pos.y, &boss_rect);
	legs->foot1->Draw();
	legs->foot2->Draw();
	legs->foot3->Draw();
	legs->foot4->Draw();

}

void Boss::UpdateLegs()
{
	eye_1 = { pos.x + 114,pos.y + 2 };
	eye_2 = { pos.x + 8,pos.y + 98 };
	eye_3 = { pos.x + 220,pos.y + 98 };
	eye_4 = { pos.x + 114,pos.y + 211 };

	int x = 0, y = 0;
	//UPDATE PIVOTS
	legs->foot1->UpdatePivots();
	legs->foot2->UpdatePivots();
	legs->foot3->UpdatePivots();
	legs->foot4->UpdatePivots();

	GetEvent();
	ExecuteEvent();

	legs->foot1->collider->SetPos(legs->foot1->pos.x - 16, legs->foot1->pos.y - 16, legs->foot1->logic_height);
	legs->foot2->collider->SetPos(legs->foot2->pos.x - 16, legs->foot2->pos.y - 16, legs->foot2->logic_height);
	legs->foot3->collider->SetPos(legs->foot3->pos.x - 16, legs->foot3->pos.y - 16, legs->foot3->logic_height);
	legs->foot4->collider->SetPos(legs->foot4->pos.x - 16, legs->foot4->pos.y - 16, legs->foot4->logic_height);
	collider->SetPos(pos.x, pos.y, logic_height);
	eye_collider->SetPos(centre_pos.x, centre_pos.y, logic_height+1);
	
	eye1_collider->SetPos(eye_1.x, eye_1.y, logic_height);
	eye2_collider->SetPos(eye_2.x, eye_2.y, logic_height);
	eye3_collider->SetPos(eye_3.x, eye_3.y, logic_height);
	eye4_collider->SetPos(eye_4.x, eye_4.y, logic_height);
}

void Boss::GetEvent()
{
	if (state == boss_idle)
		int x = 0;
	iPoint diference_point_link = { App->player->Link->pos.x - centre_pos.x,App->player->Link->pos.y - centre_pos.y };
	iPoint diference_point_zelda = { App->player->Zelda->pos.x - centre_pos.x,App->player->Zelda->pos.y - centre_pos.y };
	int dist_link = (int)(sqrt(diference_point_link.x *diference_point_link.x + diference_point_link.y * diference_point_link.y));
	int dist_zelda = (int)(sqrt(diference_point_zelda.x *diference_point_zelda.x + diference_point_zelda.y * diference_point_zelda.y));
	if (dist_link > 300 && dist_zelda >400 && can_move) {
		state = boss_move;
	}
	else if(can_attack) {
		switch (actual_phase) {
		case boss_phase_1:
			if (dist_link <= 300 && dist_link >120)
				state = boss_attack_link;
			else if(dist_zelda <=300 && dist_zelda >120)
				state = boss_attack_zelda;
			break;
		case boss_phase_2:
			if (!im_attacking) {
				if (dist_link / 300.0f < dist_zelda / 400.0f)
					if(dist_link >120)
					state = boss_attack_link;
				else if (state != boss_attack_link)
					if(dist_zelda >120)
					state = boss_attack_zelda;
			}
			break;
		case boss_phase_3:
			
				if (dist_link < 300 && dist_link >120 && dist_zelda> 400 && !im_attacking_laser)
					state = boss_attack_link;
				else if (dist_link > 300 && dist_zelda < 400 && dist_zelda >120 && !im_attacking)
					state = boss_attack_zelda;
				else if(dist_link < 300 && dist_link >120 && dist_zelda < 400 && dist_zelda >120)
					state = boss_attack_both;
			
		}
		
	}
	
}

void Boss::ExecuteEvent()
{
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
		actual_phase = boss_phase_3;
	}
	if (attacking_foot != nullptr) {
		if (foot_live == 0 && state != boss_state::boss_damaged) {
			pos = { (int)round((float)pos.x / 16) * 16 , (int)round((float)pos.y / 16) * 16 + 32 };
			CreateColliders();
			state = boss_state::boss_damaged;
			can_move = false;
			can_attack = false;
			logic_height = 0;
			damaged_boss_timer.Start();
		}
		/*if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && attacking_foot->actual_foot_state == after_attack) {
			pos = { (int)round((float)pos.x / 16) * 16 , (int)round((float)pos.y / 16) * 16 + 32 };
			CreateColliders();
			state = boss_damaged;
			can_move = false;
			can_attack = false;
			logic_height = 0;
		}*/
		if (damaged_boss_timer.Read() > 9000 && state == boss_state::boss_damaged) {
			recover_collider = App->collision->AddCollider({ pos.x,pos.y,244,244 }, collider_boss_recover, this, App->enemy);
			recover_collider->logic_height = 1;
			recover_collider->to_delete = true;
		}
		if (damaged_boss_timer.Read() > 10000 && state == boss_state::boss_damaged) {			
			DeleteColliders();
			pos = { (int)round((float)pos.x / 16) * 16 , (int)round((float)pos.y / 16) * 16 - 32 };
			can_attack = true;
			state = boss_idle;
			logic_height = 1;
			attacking_foot->actual_foot_state == back_to_start;
			foot_live = 5;
			
		}
		
	}
		if (state == boss_move) {
			attacking_foot = nullptr;
			Move();
		}
		if (state == boss_attack_link) {
			Attack(App->player->Link);		
	}
		if (state == boss_attack_zelda) {
			if (actual_phase == boss_phase_1)
				Attack(App->player->Zelda);
			else {
				LaserAttack();
			}
		}
		if (state == boss_attack_both) {
			Attack(App->player->Link);
			LaserAttack();
		}
}

void Boss::Move()
{
	int time = 10;
	
	
	static iPoint first_point = legs->foot1->pos;
	static iPoint second_point = legs->foot3->pos;
	iPoint link_pos = App->player->Link->pos;
	static iPoint player_point = App->player->Link->pos;
	static float module = 0;

	can_attack = false;
	if (moving_state == 0) {
		if (count == 0) {
			first_point = legs->foot1->pos;
			second_point = legs->foot3->pos;
			player_point = { centre_pos.x - link_pos.x ,  centre_pos.y - link_pos.y };
			module = sqrt(player_point.x * player_point.x + player_point.y * player_point.y);
			player_point = { (int)((player_point.x / module) * 64),(int)((player_point.y / module) * 64) };
			legs->foot1->logic_height = 1;
			legs->foot3->logic_height = 1;
			legs->foot2->logic_height = 0;
			legs->foot4->logic_height = 0;
		}
		legs->foot1->pos = { (int)(first_point.x - player_point.x * (count / time)),(int)(first_point.y - player_point.y * (count / time)) };
		legs->foot3->pos = { (int)(second_point.x - player_point.x * (count / time)),(int)(second_point.y - player_point.y * (count / time)) };

	}
	if (moving_state == 1) {
		if (count == 0) {
			first_point = pos;
			legs->foot1->logic_height = 0;
			legs->foot3->logic_height = 0;
		}
		pos = { (int)(first_point.x - player_point.x * (count / time)), (int)(first_point.y - player_point.y * (count / time)) };

	}
	if (moving_state == 2) {
		if (count == 0) {
			first_point = legs->foot2->pos;
			second_point = legs->foot4->pos;
			legs->foot2->logic_height = 1;
			legs->foot4->logic_height = 1;


		}
		legs->foot2->pos = { (int)(first_point.x - player_point.x * (count / time)),(int)(first_point.y - player_point.y * (count / time)) };
		legs->foot4->pos = { (int)(second_point.x - player_point.x * (count / time)),(int)(second_point.y - player_point.y * (count / time)) };

	}
	count++;
	if (count > time) {
		count = 0;
		if (moving_state == 2) {
			state = boss_idle;
			can_attack = true;
		}
		moving_state++;
		moving_state = moving_state % 3;
		
	}

}

void Boss::Attack(Character* focused_character)
{
	
	static float inc_x = 0;
	static float inc_y = 0;

	static fPoint f_foot_pos = { 0,0 };
	static fPoint start_foot_point = { 0,0 };
	
	static fPoint temp_point = { 0,0 };

	static j1Timer following_time;
	static j1Timer static_foot_time;

	
	int actual_dist = (int)(sqrt(((focused_character->pos.x - centre_pos.x) * (focused_character->pos.x - centre_pos.x)) + ((focused_character->pos.y - centre_pos.y)) * (focused_character->pos.y - centre_pos.y)));
	

	
	if (attacking_foot == nullptr) {
		int dist = (int)(sqrt(((focused_character->pos.x - legs->foot1->pos.x) * (focused_character->pos.x - legs->foot1->pos.x)) + ((focused_character->pos.y - legs->foot1->pos.y)) * (focused_character->pos.y - legs->foot1->pos.y)));
		attacking_foot = legs->foot1;
		

		if (dist > (int)(sqrt(((focused_character->pos.x - legs->foot2->pos.x) * (focused_character->pos.x - legs->foot2->pos.x)) + ((focused_character->pos.y - legs->foot2->pos.y)) * (focused_character->pos.y - legs->foot2->pos.y)))) {
			attacking_foot = legs->foot2;
			dist = (int)(sqrt(((focused_character->pos.x - legs->foot2->pos.x) * (focused_character->pos.x - legs->foot2->pos.x)) + ((focused_character->pos.y - legs->foot2->pos.y)) * (focused_character->pos.y - legs->foot2->pos.y)));

		}
		if (dist > (int)(sqrt(((focused_character->pos.x - legs->foot3->pos.x) * (focused_character->pos.x - legs->foot3->pos.x)) + ((focused_character->pos.y - legs->foot3->pos.y)) * (focused_character->pos.y - legs->foot3->pos.y)))) {
			attacking_foot = legs->foot3;
			dist = (int)(sqrt(((focused_character->pos.x - legs->foot3->pos.x) * (focused_character->pos.x - legs->foot3->pos.x)) + ((focused_character->pos.y - legs->foot3->pos.y)) * (focused_character->pos.y - legs->foot3->pos.y)));

		}
		if (dist > (int)(sqrt(((focused_character->pos.x - legs->foot4->pos.x) * (focused_character->pos.x - legs->foot4->pos.x)) + ((focused_character->pos.y - legs->foot4->pos.y)) * (focused_character->pos.y - legs->foot4->pos.y)))) {
			attacking_foot = legs->foot4;
			dist = (int)(sqrt(((focused_character->pos.x - legs->foot4->pos.x) * (focused_character->pos.x - legs->foot4->pos.x)) + ((focused_character->pos.y - legs->foot4->pos.y)) * (focused_character->pos.y - legs->foot4->pos.y)));

		}
	
		inc_x = (float)(focused_character->pos.x - attacking_foot->pos.x) / 20;
		inc_y = (float)((focused_character->pos.y - 100) - attacking_foot->pos.y) / 20;

		temp_point = { (float)attacking_foot->pos.x, (float)attacking_foot->pos.y };
		attacking_foot->actual_foot_state = charging;
		f_foot_pos = { (float)attacking_foot->pos.x, (float)attacking_foot->pos.y };
		start_foot_point = {(float)attacking_foot->pos.x, (float)attacking_foot->pos.y};
		im_attacking = true;
		can_move = false;
	}

	else {
		
		static int i = 0;
		
		iPoint above_link_point = { focused_character->pos.x, focused_character->pos.y - 100 };

		if ((actual_dist > 300 ||  actual_dist < 120) && attacking_foot->actual_foot_state != back_to_start) {
			attacking_foot->actual_foot_state = back_to_start;
			inc_x = (float)(start_foot_point.x - attacking_foot->pos.x) / 40;
			inc_y = (float)((start_foot_point.y) - attacking_foot->pos.y) / 40;
			i = 0;
			attacking_foot->logic_height = 1;
			if (attacking_foot->foot_collider_tiles.size() > 0) {
				attacking_foot->DeleteFootColliders();
			}
		}

		if (i <20 && attacking_foot->actual_foot_state == charging) {
			inc_x = (float)(focused_character->pos.x - temp_point.x) / 20;
			inc_y = (float)((focused_character->pos.y - 100) - temp_point.y) / 20;
			f_foot_pos = { f_foot_pos.x + inc_x, f_foot_pos.y + inc_y };
			i++;
			attacking_foot->logic_height = 1;
			if (i == 20) {
				i = 0;
				attacking_foot->actual_foot_state = following;
				following_time.Start();
			}
		}
		if (attacking_foot->actual_foot_state == following ) {
			if(following_time.Read() < 2000)
				f_foot_pos = { (float)focused_character->pos.x , (float)(focused_character->pos.y - 100) };
			else {
				attacking_foot->actual_foot_state = attacking;
				inc_x = (float)(focused_character->pos.x - attacking_foot->pos.x) / 10;
				inc_y = (float)((focused_character->pos.y) - attacking_foot->pos.y) / 10;
				
			}
		}
		if (i < 10 && attacking_foot->actual_foot_state == attacking) {
			f_foot_pos = { f_foot_pos.x + inc_x, f_foot_pos.y + inc_y };
			i++;
			attacking_foot->logic_height = 0;
			if (i == 10) {
				i = 0;
				static_foot_time.Start();
				attacking_foot->actual_foot_state = after_attack;
				Collider* temp_collider = App->collision->AddCollider({ (int)f_foot_pos.x,(int)f_foot_pos.y,64,64 }, COLLIDER_TYPE::collider_boss_hit, attacking_foot, App->enemy);
				temp_collider->logic_height = 0;
				temp_collider->to_delete = true;
				attacking_foot->CreateFootColliders();
			}

		}
		if (attacking_foot->actual_foot_state == after_attack) {
			if (static_foot_time.Read() > 2000) {
				attacking_foot->actual_foot_state = back_to_start;
				inc_x = (float)(start_foot_point.x - attacking_foot->pos.x) / 40;
				inc_y = (float)((start_foot_point.y) - attacking_foot->pos.y) / 40;
				attacking_foot->DeleteFootColliders();
			}
		}
		if ( i < 40 && attacking_foot->actual_foot_state == back_to_start) {
			f_foot_pos = { f_foot_pos.x + inc_x, f_foot_pos.y + inc_y };
			i++;
			attacking_foot->logic_height = 1;
			if (i == 40) {
				i = 0;
				attacking_foot->actual_foot_state = foot_idle;
				im_attacking = false;
				attacking_foot->logic_height = 0;
				state = boss_idle;
			}
		}
		
	}
	attacking_foot->pos = { (int)f_foot_pos.x, (int)f_foot_pos.y };
	if (!im_attacking) {
		attacking_foot = nullptr;
		if(!im_attacking_laser)
		can_move = true;
		state = boss_idle;
	}
}

void Boss::LaserAttack()
{
	

	static iPoint focus_eye = eye_1;


	static iPoint focus_point_before_attack = { 0,0 };
	static j1Timer laser_charging_time;
	static bool first_loop = true;

	if (first_loop) {
		can_move = false;
		im_attacking_laser = true;
		laser_charging_time.Start();
		first_loop = false;
		int dist = (int)(sqrt(((App->player->Zelda->pos.x - eye_1.x + 4) * (App->player->Zelda->pos.x - eye_1.x + 4)) + ((App->player->Zelda->pos.y - eye_1.y + 4)) * (App->player->Zelda->pos.y - eye_1.y + 4)));
		focus_eye = eye_1;
		if (dist > (int)(sqrt(((App->player->Zelda->pos.x - eye_2.x + 4) * (App->player->Zelda->pos.x - eye_2.x + 4)) + ((App->player->Zelda->pos.y - eye_2.y + 4)) * (App->player->Zelda->pos.y - eye_2.y + 4)))) {
			focus_eye = eye_2;
			dist = (int)(sqrt(((App->player->Zelda->pos.x - eye_2.x + 4) * (App->player->Zelda->pos.x - eye_2.x + 4)) + ((App->player->Zelda->pos.y - eye_2.y + 4)) * (App->player->Zelda->pos.y - eye_2.y + 4)));

		}
		if (dist > (int)(sqrt(((App->player->Zelda->pos.x - eye_3.x + 4) * (App->player->Zelda->pos.x - eye_3.x + 4)) + ((App->player->Zelda->pos.y - eye_3.y + 4)) * (App->player->Zelda->pos.y - eye_3.y + 4)))) {
			focus_eye = eye_3;
			dist = (int)(sqrt(((App->player->Zelda->pos.x - eye_3.x + 4) * (App->player->Zelda->pos.x - eye_3.x + 4)) + ((App->player->Zelda->pos.y - eye_3.y + 4)) * (App->player->Zelda->pos.y - eye_3.y + 4)));
		
		}
		if (dist > (int)(sqrt(((App->player->Zelda->pos.x - eye_4.x + 4) * (App->player->Zelda->pos.x - eye_4.x + 4)) + ((App->player->Zelda->pos.y - eye_4.y + 4)) * (App->player->Zelda->pos.y - eye_4.y + 4)))) {
			focus_eye = eye_4;
			dist = (int)(sqrt(((App->player->Zelda->pos.x - eye_4.x + 4) * (App->player->Zelda->pos.x - eye_4.x + 4)) + ((App->player->Zelda->pos.y - eye_4.y + 4)) * (App->player->Zelda->pos.y - eye_4.y + 4)));

		}

	}

	iPoint vect = { 0,0 };
	float angle = 0;
	if (laser_charging_time.Read() < 2000) {
		for (float i = 0; i < 1; i += 1.0f / 60.0f) {
			int x = (focus_eye.x + 4) * (1 - i) + App->player->Zelda->pos.x * i;
			int y = (focus_eye.y + 4)  * (1 - i) + App->player->Zelda->pos.y * i;
			vect = { App->player->Zelda->pos.x -( focus_eye.x+4), App->player->Zelda->pos.y - (focus_eye.y+4) };
			angle = atan2(vect.y, vect.x) * 57.2957795;
			App->render->Blit(boss_atlas, x, y,&laser_rect,1.0f,angle);
			App->render->Blit(boss_atlas, App->player->Zelda->pos.x, App->player->Zelda->pos.y, &laser_aim);
			focus_point_before_attack = { App->player->Zelda->pos.x,App->player->Zelda->pos.y};
			
		}
	}
	if (laser_charging_time.Read() > 2000 && laser_charging_time.Read() < 2500) {
		for (float i = 0; i < 1; i += 1.0f / 60.0f) {
			int x = (focus_eye.x + 4) * (1 - i) + focus_point_before_attack.x * i;
			int y = (focus_eye.y + 4)* (1 - i) + focus_point_before_attack.y * i;
			vect = { App->player->Zelda->pos.x - (focus_eye.x+4), App->player->Zelda->pos.y - (focus_eye.y+4) };
			angle = atan2(vect.y, vect.x) * 57.2957795;
			App->render->Blit(boss_atlas, x, y, &laser_rect_fire, 1.0f, angle);
			App->render->Blit(boss_atlas, focus_point_before_attack.x, focus_point_before_attack.y, &laser_aim);
			
		}
	}
	if (laser_charging_time.Read() > 2500) {
		//Create collider
		Collider* temp_collider = App->collision->AddCollider({ focus_point_before_attack.x,focus_point_before_attack.y - 32,64,64 }, collider_boss_explosion, this, App->enemy);
		temp_collider->logic_height = App->player->Zelda->logic_height;
		temp_collider->to_delete = true;
		laser_charging_time.Start();
		first_loop = true;
		if(!im_attacking)
		can_move = true;
		im_attacking_laser = false;
		state = boss_idle;
	}
}

void Boss::CreateColliders()
{
	centre_pos = { pos.x + collider->rect.w / 2 , pos.y + collider->rect.h / 2 };
	std::vector<iPoint> temp_vector;
	for (int i = 0; i < collider->rect.w / 16; i++) {
		for (int n = 0; n < collider->rect.h / 16; n++) {
			iPoint temp;
			temp.x = pos.x + 8 + i * 16;
			temp.y = pos.y + 8 + n * 16;
			//object.collider_tiles.push_back(temp);
			//if(App->map->V_Colision[0][object.logic_height].data[temp.y*App->map->data.width + temp.x] != App->map->CANT_PASS_COL_ID)	{
			if (App->map->V_Colision[0]->data != nullptr)
				if (App->map->V_Colision[0]->data[(temp.y / 16) * App->map->data.height + temp.x / 16] != App->map->TILE_COL_ID)
				{
					iPoint diference_point = { temp.x - centre_pos.x, temp.y - centre_pos.y };
					int dist = (int)(sqrt(diference_point.x *diference_point.x + diference_point.y * diference_point.y));
					if ((dist < 120 && dist >= 100) ) {
						App->map->V_Colision[0]->data[(temp.y / 16) * App->map->data.height + temp.x / 16] = App->map->TILE_COL_ID;
						//object.collider_tiles.push_back(temp);
						temp_vector.push_back(temp);
					}
				}
			if (App->map->V_Colision[1]->data != nullptr)
				if (App->map->V_Colision[1]->data[(temp.y / 16) *  App->map->data.height + temp.x / 16] != App->map->TILE_COL_ID)
				{
					iPoint diference_point = { temp.x - centre_pos.x, temp.y - centre_pos.y };
					int dist = sqrt(diference_point.x *diference_point.x + diference_point.y * diference_point.y);
					if (dist < 80 && dist >= 60) {
						App->map->V_Colision[1]->data[((temp.y - 16)  / 16) *  App->map->data.height + temp.x / 16] = App->map->TILE_COL_ID;
						//object.collider_tiles.push_back(temp);
						temp_vector.push_back(temp);
					}
				}
		}
	}
	colision_tiles_vec = temp_vector;

	jump_1 = App->object->CreateJump({centre_pos.x - 72,centre_pos.y - 56,16,80}, 1);
	jump_2 = App->object->CreateJump({ centre_pos.x + 56,centre_pos.y - 56,16,80 }, 1);
	jump_3 = App->object->CreateJump({ centre_pos.x - 40,centre_pos.y - 88,80,16 }, 1);
	jump_4 = App->object->CreateJump({ centre_pos.x - 40,centre_pos.y + 40,80,16 }, 1);
}

void Boss::DeleteColliders()
{
	/*
	for (int i = 0; i < colision_tiles_vec.size(); i++) {
		App->map->V_Colision[0]->data[(colision_tiles_vec[i].y / 16) *  App->map->data.height + colision_tiles_vec[i].x / 16] = NOT_COLISION_ID;
		App->map->V_Colision[1]->data[(colision_tiles_vec[i].y / 16) *  App->map->data.height + colision_tiles_vec[i].x / 16] = NOT_COLISION_ID;
	}
	*/
	for (int i = 0; i < collider->rect.w / 16; i++) {
		for (int n = 0; n < collider->rect.h / 16; n++) {
			iPoint temp;
			temp.x = pos.x + 8 + i * 16;
			temp.y = pos.y + 8 + n * 16;
			App->map->V_Colision[0]->data[(temp.y / 16) * App->map->data.height + temp.x / 16] = NOT_COLISION_ID;
			App->map->V_Colision[1]->data[((temp.y - 16) / 16) *  App->map->data.height + temp.x / 16] = NOT_COLISION_ID;
		}
	}
	colision_tiles_vec.clear();
	std::vector<Object*>::iterator it = App->object->V_Objects.begin();
	while (it != App->object->V_Objects.end()) {
		if ((*it) == jump_1 || (*it) == jump_2 || (*it) == jump_3 || (*it) == jump_4) {
			(*it)->collider->to_delete = true;
			it = App->object->V_Objects.erase(it);
			
		}
	}
   //App->object->V_Objects
}

Boss::Boss()
{
		Legs temp_legs;
		temp_legs.parent_boss = this;
		pos = { 200,200 };

		collider = App->collision->AddCollider({ pos.x,pos.y, 240,240 }, collider_boss, this, (j1Module*)App->enemy);
		centre_pos = { pos.x + collider->rect.w / 2 , pos.y + collider->rect.h / 2 };
		eye_collider = App->collision->AddCollider({ centre_pos.x,centre_pos.y, 32,32 }, collider_boss_eye, this, (j1Module*)App->enemy);
		legs = new Legs(temp_legs);

		boss_atlas = App->tex->Load("textures/boss_spritesheet.png");

		boss_rect = { 0,0,244,244 };
		laser_rect = { 293,0,4,4 };
		laser_rect_fire = { 293,4,6,10 };
		laser_aim = { 274,0,18,18 };
		leg_rect = { 276,20,14,22 };

		//boss_texture = App->tex->Load("textures/boss.png");
		//laser_texture = App->tex->Load("textures/point.png");
		logic_height = 1;
		
		eye1_collider = App->collision->AddCollider({ eye_1.x,eye_1.y,16,16 }, collider_boss_little_eye, this, App->enemy);
		eye2_collider = App->collision->AddCollider({ eye_2.x,eye_2.y,16,16 }, collider_boss_little_eye, this, App->enemy);
		eye3_collider = App->collision->AddCollider({ eye_3.x,eye_3.y,16,16 }, collider_boss_little_eye, this, App->enemy);
		eye4_collider = App->collision->AddCollider({ eye_4.x,eye_4.y,16,16 }, collider_boss_little_eye, this, App->enemy);

		eye_1_tex = { 266,0,8,6 };
		eye_2_tex = { 244,0,8,10 };
		eye_3_tex = { 244,10,8,10 };
		eye_4_tex = { 252,0,14,13 };
}

Boss::~Boss()
{
	App->tex->UnLoad(boss_atlas);
	legs = NULL;
	delete legs;
	attacking_foot = nullptr;
	state = boss_idle;

	for (int i = 0; i < colision_tiles_vec.size(); i++) {
		App->map->V_Colision[0]->data[(colision_tiles_vec[i].y / 16) * 100 + colision_tiles_vec[i].x / 16] = NOT_COLISION_ID;
		App->map->V_Colision[1]->data[(colision_tiles_vec[i].y / 16) * 100 + colision_tiles_vec[i].x / 16] = NOT_COLISION_ID;
	}
	colision_tiles_vec.clear();
	std::vector<Object*>::iterator it = App->object->V_Objects.begin();
	while (it != App->object->V_Objects.end()) {
		if ((*it) == jump_1 || (*it) == jump_2 || (*it) == jump_3 || (*it) == jump_4) {
			(*it)->collider->to_delete = true;
			it = App->object->V_Objects.erase(it);

		}
	}

}

void Foot::Draw()
{
	int x = 0;
	int y = 0;
	fPoint point1 = { 0,0 };
	fPoint point2 = { 0,0 };
	fPoint vect = { 0,0 };

	float cos_angle = 0;
	float angle = 0;
	
	if (actual_foot_state == foot_state::after_attack) {
		App->render->Blit(parent_boss->boss_atlas, pos.x - 16, pos.y - 16, &foot_rect);
	}
	else {
		App->render->Blit(parent_boss->boss_atlas, pos.x - 16, pos.y - 16, &foot_rect_invulnerable);
	}
	for (float i = 0; i <= 1; i += 1.0f/20.0f) {
		x = ((1-i)*(1-i) * pos.x + 2*i*(1-i)*max_point.x + i*i*pivot_point.x);
		y = ((1 - i)*(1 - i) * pos.y + 2 * i*(1 - i)*max_point.y + i*i*pivot_point.y);
		point1 = { pos.x*(1 - i) + max_point.x*i,pos.y * (1 - i) + max_point.y * i };
		point2 = { max_point.x*(1 - i) + pivot_point.x*i,max_point.y * (1 - i) + pivot_point.y * i };
		vect = { point2.x - point1.x,point2.y - point1.y };
		angle = atan2(vect.y, vect.x) * 57.2957795;
		App->render->Blit(parent_boss->boss_atlas, x, y, &parent_boss->leg_rect,1.0f,angle + 90);
	}

}

void Foot::UpdatePivots()
{
	parent_boss->centre_pos = { parent_boss->pos.x + parent_boss->collider->rect.w / 2 ,  parent_boss->pos.y + parent_boss->collider->rect.h / 2 };
	pivot_point = { parent_boss->pos.x + parent_offset.x, parent_boss->pos.y +parent_offset.y};
	max_point = { (int)(pos.x - (float)(pos.x-pivot_point.x)/1.5), pivot_point.y - 50 - abs(pos.y - pivot_point.y) };
}

void Foot::CreateFootColliders()
{
	iPoint temp = { 0,0 };
	for (int i = 1; i < foot_rect.w / 16 - 1; i++) {
		for (int n = 1; n < foot_rect.h / 16 - 1; n++) {
			temp.x = pos.x + i * 16;
			temp.y = pos.y + n * 16;
			if (App->map->V_Colision[0]->data[(temp.y / 16) * App->map->data.height + temp.x / 16] == NOT_COLISION_ID) {
				App->map->V_Colision[0]->data[(temp.y / 16) * App->map->data.height + temp.x / 16] = App->map->CANT_PASS_COL_ID;
				foot_collider_tiles.push_back(temp);
			}
		}
	}
}

void Foot::DeleteFootColliders()
{
	iPoint temp = { 0,0 };
	for (int i = 0; i < foot_collider_tiles.size(); i++) {
		App->map->V_Colision[0]->data[(foot_collider_tiles[i].y / 16) * App->map->data.height + foot_collider_tiles[i].x / 16] = NOT_COLISION_ID;
	}
	foot_collider_tiles.clear();
}

Foot::Foot(const Foot& obj)
{
	pos = obj.pos;
	max_point = obj.max_point;
	pivot_point = obj.pivot_point;
	parent_boss = obj.parent_boss;
	collider = App->collision->AddCollider({ pos.x,pos.y, 64,64 }, collider_boss_foot, this, (j1Module*)App->enemy);
	//leg = App->tex->Load("textures/point.png");
	parent_offset = obj.parent_offset;
	foot_rect = { 299,0,64,64 };
	foot_rect_invulnerable = { 363,0,64,64 };
}

Foot::~Foot()
{
}
