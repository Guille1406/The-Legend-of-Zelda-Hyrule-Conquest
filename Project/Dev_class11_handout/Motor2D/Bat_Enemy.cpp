#include "Bat_Enemy.h"
#include"Color.h"
Bat_Enemy::Bat_Enemy() :Enemy(enemyType::bat_enemy)
{
	this->sprites_vector = App->enemy->enemy_bat_perf->sprites_vector;
	this->entity_texture = App->enemy->enemy_bat_perf->entity_texture;
	this->ChangeAnimation(1);
}

Bat_Enemy::Bat_Enemy(const Bat_Enemy &r_enemy) :Enemy(enemyType::bat_enemy)
{
	this->collider = r_enemy.collider;
	this->logic_height = r_enemy.logic_height;
	this->sprites_vector = App->enemy->enemy_bat_perf->sprites_vector;

}


Bat_Enemy::~Bat_Enemy()
{
}

void Bat_Enemy::Action()
{
	tile_pos.x = pos.x / 16;
	tile_pos.y = pos.y / 16;

	SDL_Rect shadow_rect = { pos.x ,pos.y+15, collider->rect.w, collider->rect.h-10 };
	App->render->DrawQuad(shadow_rect, Black(0), Black(1), Black(2), 50, true);

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
