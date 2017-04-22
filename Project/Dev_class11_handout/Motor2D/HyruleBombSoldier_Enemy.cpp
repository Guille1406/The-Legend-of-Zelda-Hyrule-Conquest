#include "HyruleBombSoldier_Enemy.h"
#include"j1Enemy.h"
#include"j1Player.h"
#include"Color.h"
HyruleBombSoldier_Enemy::HyruleBombSoldier_Enemy() :Enemy(enemyType::hyrulebombsoldier_enemy)
{
	this->sprites_vector = App->enemy->enemy_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_perf->entity_texture;
	this->ChangeAnimation(1);
}

HyruleBombSoldier_Enemy::HyruleBombSoldier_Enemy(const HyruleBombSoldier_Enemy& chs_enemy) :Enemy(enemyType::hyrulebombsoldier_enemy)
{
	this->collider = chs_enemy.collider;
	this->logic_height = chs_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_perf->sprites_vector;
}

HyruleBombSoldier_Enemy::~HyruleBombSoldier_Enemy()
{
}

void HyruleBombSoldier_Enemy::Action()
{
	//printing the bomb

	SDL_Rect p = { bomb_point.x ,bomb_point.y, 10,10 };
	App->render->DrawQuad(p, Black(0), Black(1), Black(2), 255, true);
	if (can_throw_bomb==true && player_in_range!=nullptr) {
		player_position = player_in_range->pos;
		t = 0;
		bomb_timer.Start();
	//	continue_path_bomb = true;
		can_throw_bomb = false;
	}

	off_set = 100;
	if (player_position.x<pix_world_pos.x) {
		off_set = -100;
	}
	max_bomb_point.x = pix_world_pos.x + off_set;

	if (state == EnemyState::throwing_bomb || t<1) {
		
		bomb_point.x = (1 - t)*(1 - t)*pix_world_pos.x + 2 * t*(1 - t)*max_bomb_point.x + t*t*player_position.x;
		bomb_point.y = (1 - t)*(1 - t)*pix_world_pos.y + 2 * t*(1 - t)*max_bomb_point.y + t*t*player_position.y;
		
		if (t < 1) {
			t += (float)1 / 100;
		}
		else {
			//bomb.bomb_collider_explosion = App->collision->AddCollider(p, COLLIDER_TYPE::coolider_bomb_explosion, this, App->enemy);
			if (bomb_timer.Read() > 5000) {
				t = 0;
				can_throw_bomb = true;
			}
		}
	

	}
}

