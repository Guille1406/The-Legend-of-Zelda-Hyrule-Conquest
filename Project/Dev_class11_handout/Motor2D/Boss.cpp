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
	
	/*
	foot1->parent_offset = { 50,30 };
	foot1->pos = { parent_boss->centre_pos.x - 200, parent_boss->centre_pos.y };
	foot1->pivot_point = { parent_boss->pos.x + foot1->parent_offset.x, parent_boss->pos.y + foot1->parent_offset.y };
	foot1->max_point = { (int)(foot1->pos.x - (float)(foot1->pos.x - foot1->pivot_point.x) / 1.5),foot1->pivot_point.y - 50 - abs(foot1->pos.y - foot1->pivot_point.y) };

	foot2->parent_offset = { 180,30 };
	foot2->pos = { parent_boss->centre_pos.x + 200, parent_boss->centre_pos.y };
	foot2->pivot_point = { parent_boss->pos.x + foot2->parent_offset.x, parent_boss->pos.y + foot2->parent_offset.y };
	foot2->max_point = { (int)(foot2->pos.x - (float)(foot2->pos.x - foot2->pivot_point.x) / 1.5),foot2->pivot_point.y - 50 - abs(foot2->pos.y - foot2->pivot_point.y) };


	foot3->pos = { parent_boss->centre_pos.x - 200, parent_boss->centre_pos.y + 150 };
	foot3->parent_offset = { 50,180 };
	foot3->pivot_point = { parent_boss->pos.x + foot3->parent_offset.x, parent_boss->pos.y + foot3->parent_offset.y };
	foot3->max_point = { (int)(foot3->pos.x - (float)(foot3->pos.x - foot3->pivot_point.x) / 1.5),foot3->pivot_point.y - 50 - abs(foot3->pos.y - foot3->pivot_point.y) };


	foot4->pos = { parent_boss->centre_pos.x + 200, parent_boss->centre_pos.y + 150 };
	foot4->parent_offset = { 180,180 };
	foot4->pivot_point = { parent_boss->pos.x + foot4->parent_offset.x, parent_boss->pos.y + foot4->parent_offset.y };
	foot4->max_point = { (int)(foot4->pos.x - (float)(foot4->pos.x - foot4->pivot_point.x) / 1.5),foot4->pivot_point.y - 50 - abs(foot4->pos.y - foot4->pivot_point.y) };
	*/
}

void Boss::Draw(int height)
{
	if(height == logic_height)
	App->render->Blit(boss_texture, pos.x, pos.y);
	legs->foot1->Draw();
	legs->foot2->Draw();
	legs->foot3->Draw();
	legs->foot4->Draw();

}

void Boss::UpdateLegs()
{
	int x = 0, y = 0;
	//UPDATE PIVOTS
	legs->foot1->UpdatePivots();
	legs->foot2->UpdatePivots();
	legs->foot3->UpdatePivots();
	legs->foot4->UpdatePivots();

	GetEvent();
	ExecuteEvent();

	legs->foot1->collider->SetPos(legs->foot1->pos.x, legs->foot1->pos.y, legs->foot1->logic_height);
	legs->foot2->collider->SetPos(legs->foot2->pos.x, legs->foot2->pos.y, legs->foot2->logic_height);
	legs->foot3->collider->SetPos(legs->foot3->pos.x, legs->foot3->pos.y, legs->foot3->logic_height);
	legs->foot4->collider->SetPos(legs->foot4->pos.x, legs->foot4->pos.y, legs->foot4->logic_height);
	collider->SetPos(pos.x, pos.y, logic_height);
}

void Boss::GetEvent()
{
	iPoint diference_point = { App->player->Link->pos.x - centre_pos.x,App->player->Link->pos.y - centre_pos.y };
	int dist = sqrt(diference_point.x *diference_point.x + diference_point.y * diference_point.y);
	if (dist > 300 && can_move) {
		state = boss_move;
	}
	else if(can_attack) {
		state = boss_attack;
	}
	
}

void Boss::ExecuteEvent()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && attacking_foot->actual_foot_state == after_attack) {
		pos = { (int)round((float)pos.x / 16) * 16 , (int)round((float)pos.y / 16) * 16 + 32};
		CreateColliders();
		state = boss_damaged;
		can_move = false;
		can_attack = false;
		logic_height = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN && state == boss_damaged) {
		DeleteColliders();
		pos = { (int)round((float)pos.x / 16) * 16 , (int)round((float)pos.y / 16) * 16 - 32 };
		can_attack = true;
		state = boss_idle;
		logic_height = 1;
		attacking_foot->actual_foot_state == back_to_start;
	}
	if (state == boss_move) {
		attacking_foot = nullptr;
		Move();
	}
	if (state == boss_attack) {
		Attack();
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

void Boss::Attack()
{
	
	static float inc_x = 0;
	static float inc_y = 0;

	static fPoint f_foot_pos = { 0,0 };
	static fPoint start_foot_point = { 0,0 };
	
	static fPoint temp_point = { 0,0 };

	static j1Timer following_time;
	static j1Timer static_foot_time;
	
	int actual_dist = sqrt(((App->player->Link->pos.x - centre_pos.x) * (App->player->Link->pos.x - centre_pos.x)) + ((App->player->Link->pos.y - centre_pos.y)) * (App->player->Link->pos.y - centre_pos.y));
	

	
	if (attacking_foot == nullptr) {
		int dist = sqrt(((App->player->Link->pos.x - legs->foot1->pos.x) * (App->player->Link->pos.x - legs->foot1->pos.x)) + ((App->player->Link->pos.y - legs->foot1->pos.y)) * (App->player->Link->pos.y - legs->foot1->pos.y));
		attacking_foot = legs->foot1;
		

		if (dist > sqrt(((App->player->Link->pos.x - legs->foot2->pos.x) * (App->player->Link->pos.x - legs->foot2->pos.x)) + ((App->player->Link->pos.y - legs->foot2->pos.y)) * (App->player->Link->pos.y - legs->foot2->pos.y))) {
			attacking_foot = legs->foot2;
			dist = sqrt(((App->player->Link->pos.x - legs->foot2->pos.x) * (App->player->Link->pos.x - legs->foot2->pos.x)) + ((App->player->Link->pos.y - legs->foot2->pos.y)) * (App->player->Link->pos.y - legs->foot2->pos.y));

		}
		if (dist > sqrt(((App->player->Link->pos.x - legs->foot3->pos.x) * (App->player->Link->pos.x - legs->foot3->pos.x)) + ((App->player->Link->pos.y - legs->foot3->pos.y)) * (App->player->Link->pos.y - legs->foot3->pos.y))) {
			attacking_foot = legs->foot3;
			dist = sqrt(((App->player->Link->pos.x - legs->foot3->pos.x) * (App->player->Link->pos.x - legs->foot3->pos.x)) + ((App->player->Link->pos.y - legs->foot3->pos.y)) * (App->player->Link->pos.y - legs->foot3->pos.y));

		}
		if (dist > sqrt(((App->player->Link->pos.x - legs->foot4->pos.x) * (App->player->Link->pos.x - legs->foot4->pos.x)) + ((App->player->Link->pos.y - legs->foot4->pos.y)) * (App->player->Link->pos.y - legs->foot4->pos.y))) {
			attacking_foot = legs->foot4;
			dist = sqrt(((App->player->Link->pos.x - legs->foot4->pos.x) * (App->player->Link->pos.x - legs->foot4->pos.x)) + ((App->player->Link->pos.y - legs->foot4->pos.y)) * (App->player->Link->pos.y - legs->foot4->pos.y));

		}
	
		inc_x = (float)(App->player->Link->pos.x - attacking_foot->pos.x) / 20;
		inc_y = (float)((App->player->Link->pos.y - 100) - attacking_foot->pos.y) / 20;

		temp_point = { (float)attacking_foot->pos.x, (float)attacking_foot->pos.y };
		attacking_foot->actual_foot_state = charging;
		f_foot_pos = { (float)attacking_foot->pos.x, (float)attacking_foot->pos.y };
		start_foot_point = {(float)attacking_foot->pos.x, (float)attacking_foot->pos.y};
		im_attacking = true;
		can_move = false;
	}

	else {
		
		static int i = 0;
		
		iPoint above_link_point = { App->player->Link->pos.x, App->player->Link->pos.y - 100 };

		if (actual_dist > 300 && attacking_foot->actual_foot_state != back_to_start) {
			attacking_foot->actual_foot_state = back_to_start;
			inc_x = (float)(start_foot_point.x - attacking_foot->pos.x) / 40;
			inc_y = (float)((start_foot_point.y) - attacking_foot->pos.y) / 40;
			i = 0;
			attacking_foot->logic_height = 1;
		}

		if (i <20 && attacking_foot->actual_foot_state == charging) {
			inc_x = (float)(App->player->Link->pos.x - temp_point.x) / 20;
			inc_y = (float)((App->player->Link->pos.y - 100) - temp_point.y) / 20;
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
				f_foot_pos = { (float)App->player->Link->pos.x , (float)(App->player->Link->pos.y - 100) };
			else {
				attacking_foot->actual_foot_state = attacking;
				inc_x = (float)(App->player->Link->pos.x - attacking_foot->pos.x) / 10;
				inc_y = (float)((App->player->Link->pos.y) - attacking_foot->pos.y) / 10;
				
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
			}

		}
		if (attacking_foot->actual_foot_state == after_attack) {
			if (static_foot_time.Read() > 2000) {
				attacking_foot->actual_foot_state = back_to_start;
				inc_x = (float)(start_foot_point.x - attacking_foot->pos.x) / 40;
				inc_y = (float)((start_foot_point.y) - attacking_foot->pos.y) / 40;
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
			}
		}
		
	}
	attacking_foot->pos = { (int)f_foot_pos.x, (int)f_foot_pos.y };
	if (!im_attacking) {
		attacking_foot = nullptr;
		can_move = true;
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
			//if(App->map->V_Colision[0][object.logic_height].data[temp.y*App->map->data.width + temp.x] != CANT_PASS_COL_ID)	{
			if (App->map->V_Colision[0]->data != nullptr)
				if (App->map->V_Colision[0]->data[(temp.y / 16) * 100 + temp.x / 16] != TILE_COL_ID)
				{
					iPoint diference_point = { temp.x - centre_pos.x, temp.y - centre_pos.y };
					int dist = sqrt(diference_point.x *diference_point.x + diference_point.y * diference_point.y);
					if ((dist < 120 && dist >= 100) ) {
						App->map->V_Colision[0]->data[(temp.y / 16) * 100 + temp.x / 16] = TILE_COL_ID;
						//object.collider_tiles.push_back(temp);
						temp_vector.push_back(temp);
					}
				}
			if (App->map->V_Colision[1]->data != nullptr)
				if (App->map->V_Colision[1]->data[(temp.y / 16) * 100 + temp.x / 16] != TILE_COL_ID)
				{
					iPoint diference_point = { temp.x - centre_pos.x, temp.y - centre_pos.y };
					int dist = sqrt(diference_point.x *diference_point.x + diference_point.y * diference_point.y);
					if (dist < 80 && dist >= 60) {
						App->map->V_Colision[1]->data[((temp.y - 16)  / 16) * 100 + temp.x / 16] = TILE_COL_ID;
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
   //App->object->V_Objects
}

Boss::Boss()
{
	{
		Legs temp_legs;
		temp_legs.parent_boss = this;
		pos = { 200,200 };

		collider = App->collision->AddCollider({ pos.x,pos.y, 240,240 }, collider_enemy, this, (j1Module*)App->player);
		centre_pos = { pos.x + collider->rect.w / 2 , pos.y + collider->rect.h / 2 };

		legs = new Legs(temp_legs);
		boss_texture = App->tex->Load("textures/boss.png");
		logic_height = 1;
		
	}
}

Boss::~Boss()
{
	App->tex->UnLoad(boss_texture);
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
	for (float i = 0; i <= 1; i += 0.01f) {
		x = ((1-i)*(1-i) * pos.x + 2*i*(1-i)*max_point.x + i*i*pivot_point.x);
		y = ((1 - i)*(1 - i) * pos.y + 2 * i*(1 - i)*max_point.y + i*i*pivot_point.y);
		App->render->Blit(leg, x, y);
	}
	//App->render->Blit(leg, pos.x, pos.y);
}

void Foot::UpdatePivots()
{
	parent_boss->centre_pos = { parent_boss->pos.x + parent_boss->collider->rect.w / 2 ,  parent_boss->pos.y + parent_boss->collider->rect.h / 2 };
	pivot_point = { parent_boss->pos.x + parent_offset.x, parent_boss->pos.y +parent_offset.y};
	max_point = { (int)(pos.x - (float)(pos.x-pivot_point.x)/1.5), pivot_point.y - 50 - abs(pos.y - pivot_point.y) };
}

Foot::Foot(const Foot& obj)
{
	pos = obj.pos;
	max_point = obj.max_point;
	pivot_point = obj.pivot_point;
	parent_boss = obj.parent_boss;
	collider = App->collision->AddCollider({ pos.x,pos.y, 36,36 }, collider_enemy, this, (j1Module*)App->player);
	leg = App->tex->Load("textures/point.png");
	parent_offset = obj.parent_offset;
}

Foot::~Foot()
{
}
