#include "Rope_Enemy.h"

Rope_Enemy::Rope_Enemy() :Enemy(enemyType::rope_enemy)
{
	this->sprites_vector = App->enemy->enemy_rope_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_rope_perf->entity_texture;
	this->ChangeAnimation(1);
}

Rope_Enemy::Rope_Enemy(const Rope_Enemy &r_enemy) :Enemy(enemyType::rope_enemy)
{
	this->collider = r_enemy.collider;
	this->logic_height = r_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_rope_perf->sprites_vector;

}


Rope_Enemy::~Rope_Enemy()
{
}

void Rope_Enemy::Action()
{
	tile_pos.x = pos.x / 16;
	tile_pos.y = pos.y / 16;
	if (player_in_range == nullptr) {
		iPoint actual_tile = pos;
		if (passedtile == true) {
			temp_point = array_pos;
			array_pos = App->enemy->CalculatePath(this);
			if (array_pos == temp_point) {
				Path_Enemy.clear();
			}

		}

		int x = ((array_pos.x) - temp_point.x);


		int y = ((array_pos.y) - temp_point.y);


		pos.x += x;
		pos.y += y;

		if (x == 1) {
			Enemy_Orientation = OrientationEnemy::right_enemy;
		}
		else if (x == -1) {
			Enemy_Orientation = OrientationEnemy::left_enemy;
		}
		else if (y == 1) {
			Enemy_Orientation = OrientationEnemy::down_enemy;
		}
		else if (y == -1) {
			Enemy_Orientation = OrientationEnemy::up_enemy;
		}


		if ((actual_tile.x / 16) == array_pos.x && (actual_tile.y / 16) == array_pos.y) {
			passedtile = true;
		}
		else {
			passedtile = false;
		}
	}
	else {


	}
}
