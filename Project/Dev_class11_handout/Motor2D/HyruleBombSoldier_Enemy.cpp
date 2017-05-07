#include "HyruleBombSoldier_Enemy.h"
#include"j1Enemy.h"
#include"j1Player.h"

#include"Color.h"
#include"Animation.h"
HyruleBombSoldier_Enemy::HyruleBombSoldier_Enemy() :Enemy(enemyType::hyrulebombsoldier_enemy)
{
	bomb = new Enemy_Bomb();
	Frame bomb_frame;
	bomb_frame.pivot = { 0,0 };
	bomb_frame.rect = rect_bomb;
	bomb->Explosion_animation.PushBack(bomb_frame);
	for (int i = 0; i < 11; i++) {
		bomb_frame.rect = { explosion1.x+94*i,explosion1.y,explosion1.w, explosion1.h };
		bomb->Explosion_animation.PushBack(bomb_frame);
	}
	bomb->Explosion_animation.speed = 0;

	this->sprites_vector = App->enemy->enemy_hyrulebomb_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_hyrulebomb_perf->entity_texture;
	this->ChangeAnimation(1);
	this->state = EnemyState::doing_path;
	this->can_throw_bomb = true;
}

HyruleBombSoldier_Enemy::HyruleBombSoldier_Enemy(const HyruleBombSoldier_Enemy& chs_enemy) :Enemy(enemyType::hyrulebombsoldier_enemy)
{
	bomb = new Enemy_Bomb();
	Frame bomb_frame;
	bomb_frame.pivot = { 0,0 };
	bomb_frame.rect = rect_bomb;
	bomb->Explosion_animation.PushBack(bomb_frame);
	for (int i = 1; i < 12; i++) {
		bomb_frame.rect = { explosion1.x*i,explosion1.y,explosion1.w, explosion1.h };
		bomb->Explosion_animation.PushBack(bomb_frame);
	}
	bomb->Explosion_animation.speed = 0;
	
	this->collider = chs_enemy.collider;
	this->logic_height = chs_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_hyrulebomb_perf->sprites_vector;
	this->state = EnemyState::doing_path;
	this->can_throw_bomb = true;
}

HyruleBombSoldier_Enemy::~HyruleBombSoldier_Enemy()
{
}

void HyruleBombSoldier_Enemy::Action()
{
	//printing the bomb
	if (bomb->Explosion_delay.Read()>300 && bomb->bomb_collider_explosion!=nullptr) {
		bomb->bomb_collider_explosion->to_delete = true;
	}
	SDL_Rect p = { bomb_point.x ,bomb_point.y, 10,10 };
	
	if (can_throw_bomb==true && player_in_range!=nullptr) {
		player_position = player_in_range->pos;
		t = 0;
		bomb_timer.Start();
	//	continue_path_bomb = true;
		can_throw_bomb = false;
		bomb->bomb_explosion = false;
		bomb->position = this->pos;
	}
	

	off_set = 100;
	this->Enemy_Orientation = OrientationEnemy::down_enemy;
	if (player_position.x<pos.x) {
		this->Enemy_Orientation = OrientationEnemy::left_enemy;
		off_set = -100;
	}
	else {
		this->Enemy_Orientation = OrientationEnemy::right_enemy;
	}


	max_bomb_point.x = pos.x + off_set;
	if (state == EnemyState::throwing_bomb || t<1 || bomb->bomb_explosion == false) {
		
		bomb_point.x = (1 - t)*(1 - t)*pos.x + 2 * t*(1 - t)*max_bomb_point.x + t*t*player_position.x;
		bomb_point.y = (1 - t)*(1 - t)*pos.y + 2 * t*(1 - t)*max_bomb_point.y + t*t*player_position.y;
		
		if (t < 1) {
			
			t += (float)1 / 100;
		}
		else {
			
			if (bomb_timer.Read() > 5000) {
				t = 0;
				can_throw_bomb = true;
				bomb->bomb_explosion = false;
			}
			else {
				if (bomb->bomb_explosion ==false) {
					bomb->rang_bomb = { bomb_point.x-25 ,bomb_point.y-25, 50,50 };
					bomb->bomb_collider_explosion = App->collision->AddCollider(bomb->rang_bomb, COLLIDER_TYPE::coolider_bomb_explosion, bomb, App->player);
					bomb->bomb_collider_explosion->logic_height = 0;
					bomb->Explosion_delay.Start();
					bomb->bomb_explosion = true;
					
				}
			}
		}
		if (t >=1) {
			bomb->Explosion_animation.speed = 0.0f;
		}
		if (bomb->Explosion_animation.Finished() == false) {
			bomb->texture_bomb_rect = bomb->Explosion_animation.GetCurrentFrame().rect;
			App->render->Blit(App->object->objects_texture, p.x, p.y, &bomb->texture_bomb_rect);
		}
		else {
			bomb->Explosion_animation.Reset();
			bomb->Explosion_animation.speed = 0.0f;
		}
	

	}
	
}

