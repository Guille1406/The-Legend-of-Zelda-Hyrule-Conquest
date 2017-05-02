#include "Statue_Enemy.h"

Statue_Enemy::Statue_Enemy() :Enemy(enemyType::statue_enemy)
{
	this->sprites_vector = App->enemy->enemy_statue_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_statue_perf->entity_texture;
	this->ChangeAnimation(1);
}

Statue_Enemy::Statue_Enemy(const Statue_Enemy &g_enemy) :Enemy(enemyType::statue_enemy)
{
	this->collider = g_enemy.collider;
	this->logic_height = g_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_statue_perf->sprites_vector;

}

Statue_Enemy::~Statue_Enemy()
{
}

void Statue_Enemy::Action()
{
	tile_pos.x = pix_world_pos.x / 16;
	tile_pos.y = pix_world_pos.y / 16;
	if (player_in_range == nullptr) {
		iPoint actual_tile = pix_world_pos;
		if (passedtile == true) {
			temp_point = array_pos;
			array_pos = App->enemy->CalculatePath(this);
			if (array_pos == temp_point) {
				Path_Enemy.clear();
			}

		}


		int x = ((array_pos.x) - temp_point.x);


		int y = ((array_pos.y) - temp_point.y);


		pix_world_pos.x += x;
		pix_world_pos.y += y;

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
		if (!enemy_doing_script) {
			if (this->state != jumping) {
				first_point = pix_world_pos;
				max_heigh_jump.y = pix_world_pos.y - 50;
				if (player_in_range->pos.x < pix_world_pos.x) {
					last_point.x = pix_world_pos.x - 50;
				}
				else {
					last_point.x = pix_world_pos.x + 50;
				}
				last_point.y = (player_in_range->pos.y + pix_world_pos.y) / 2;
			}

			if (abs(first_point.x - last_point.x) > abs(first_point.y - last_point.y)) {
				if (first_point.x < last_point.x) {
					Enemy_Orientation = OrientationEnemy::right_enemy;
				}
				else {
					Enemy_Orientation = OrientationEnemy::left_enemy;
				}
			}
			else {
				if (first_point.y < last_point.y) {
					Enemy_Orientation = OrientationEnemy::down_enemy;
				}
				else {
					Enemy_Orientation = OrientationEnemy::up_enemy;
				}
			}

			pix_world_pos.y = (1 - t)*(1 - t)*first_point.y + 2 * t*(1 - t)*max_heigh_jump.y + t*t*last_point.y;

			if (t < 1) {

				t += (float)1 / 50;
				if (t<=0.5) {
					this->logic_height = 1;
				}
				else {
					this->logic_height = 0;
				}
			}
			else {
				t = 0;
				this->logic_height = 0;
				first_point = last_point;
				if (player_in_range->pos.x < pix_world_pos.x) {
					last_point.x = pix_world_pos.x - 50;
				}
				else {
					last_point.x = pix_world_pos.x + 50;
				}
				max_heigh_jump.y = pix_world_pos.y - 50;
				last_point.y = (player_in_range->pos.y + pix_world_pos.y) / 2;
			}

		}
		else {
			if (script_timer.Read() > 1000)
				enemy_doing_script = false;
			
		}
	}
	
	
}
