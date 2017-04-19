#include "HyruleBombSoldier_Enemy.h"
#include"j1Enemy.h"
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
}

