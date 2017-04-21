#include "HyruleBombSoldier_Enemy.h"
#include"j1Enemy.h"
#include"j1Player.h"
HyruleBombSoldier_Enemy::HyruleBombSoldier_Enemy() :Enemy(enemyType::championsoldier_enemy)
{
	this->sprites_vector = App->enemy->enemy_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_perf->entity_texture;
	this->ChangeAnimation(1);
}

HyruleBombSoldier_Enemy::HyruleBombSoldier_Enemy(const HyruleBombSoldier_Enemy& chs_enemy) :Enemy(enemyType::championsoldier_enemy)
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
	if (state == EnemyState::throwing_bomb) {
		

		bomb_point.x = (1 - t)*(1 - t)*bomb_point.x + 2 * t*(1 - t)*max_bomb_point.x + t*t*player_in_range->pos.x;
		bomb_point.y = (1 - t)*(1 - t)*bomb_point.y + 2 * t*(1 - t)*max_bomb_point.y + t*t*player_in_range->pos.y;
			
		



	}

}

