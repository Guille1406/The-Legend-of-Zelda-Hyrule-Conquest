#include "Statue_Enemy.h"
#include"Color.h"
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
	tile_pos.x = pos.x / 16;
	tile_pos.y = pos.y / 16;
	static float inc = 0;
	static float temp = 0;
	if (t == 0) {
		temp = 0;
		if (player_in_range != nullptr) {
			inc = (float)(player_in_range->pos.y - pos.y) / 2.0;
			

			new_y = pos.y;
		}
	}
	temp += (float)inc / 50.0f;
	this->rect_en = { pos.x - 2 , new_y + (int)temp, 35, this->rect.h / 2 };
	App->render->DrawQuad(rect_en, Black(0), Black(1), Black(2), 50, true);

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
		if (!enemy_doing_script) {
			if (this->state != jumping) {
				first_point = pos;
				max_heigh_jump.y = pos.y - 50;
				/*if (player_in_range->pos.x < pos.x) {
					last_point.x = pos.x - 50;
				}
				else {
					last_point.x = pos.x + 50;
				}*/
				last_point.x = (player_in_range->pos.x + pos.x) / 2;
				last_point.y = (player_in_range->pos.y + pos.y) / 2;
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

			pos.y = (1 - t)*(1 - t)*first_point.y + 2 * t*(1 - t)*max_heigh_jump.y + t*t*last_point.y;
			if (pos.x!= last_point.x) {
				switch (Enemy_Orientation) {
				case OrientationEnemy::right_enemy:
					pos.x += 1;
					break;
				case OrientationEnemy::left_enemy:
					pos.x -= 1;
					break;
				}
				
			}
			if (t < 1) {

				t += (float)1 / 50;
				if (t<=0.15 || t >= 0.85) {
					this->logic_height = 0;
				}
				else {
					this->logic_height = 1;
				}
			}
			else {
				t = 0;
				this->logic_height = 0;
				first_point = last_point;
				if (player_in_range->pos.x < pos.x) {
					last_point.x = pos.x - 50;
				}
				else {
					last_point.x = pos.x + 50;
				}
				max_heigh_jump.y = pos.y - 50;
				last_point.y = (player_in_range->pos.y + pos.y) / 2;
			}

		}
		else {
			if (script_timer.Read() > 1000)
				enemy_doing_script = false;
			
		}
	}
	
	
}
