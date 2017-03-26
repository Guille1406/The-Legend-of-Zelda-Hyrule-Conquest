#include "Green_Enemy.h"
#include"j1Enemy.h"
#include"j1Map.h"
Green_Enemy::Green_Enemy():Enemy(enemyType::green_enemy)
{
}
Green_Enemy::Green_Enemy(const Green_Enemy& g_enemy) :Enemy(enemyType::green_enemy)
{
	this->collider = g_enemy.collider;
	this->logic_height = g_enemy.logic_height;
}

Green_Enemy::~Green_Enemy()
{
}

void Green_Enemy::Action()
{
	this->array_pos= CalculatePath();
	this->pix_world_pos.x= this->array_pos.x*App->map->data.tile_width;
	this->pix_world_pos.y = this->array_pos.y*App->map->data.tile_height;
}

iPoint Green_Enemy::CalculatePath()
{
	Path_Enemy.push_back(array_pos);
	iPoint cell;
	for (int i = 0; i < App->map->V_PathEnemies.size(); i++) {
		if (this->movable == true) {
			cell.create(array_pos.x, array_pos.y + 1);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell) == false) {
				this->Path_Enemy.push_back(cell);
				return cell;
			}
			cell.create(array_pos.x, array_pos.y - 1);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell) == false) {
				this->Path_Enemy.push_back(cell);
				return cell;
			}

			cell.create(array_pos.x + 1, array_pos.y);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell) == false) {
				this->Path_Enemy.push_back(cell);
				return cell;
			}

			cell.create(array_pos.x - 1, array_pos.y);
			if (App->map->V_PathEnemies[i]->Get(cell.x, cell.y) != 0 && FindInPath(cell) == false) {
				this->Path_Enemy.push_back(cell);
				return cell;
			}

		}
	}
	if (this->Path_Enemy.size()>1) {
		Path_Enemy.clear();
	}
	else {
		this->movable = false;
	}
	return array_pos;
}

bool Green_Enemy::FindInPath(iPoint pos) {

	for (std::list<iPoint>::iterator item = this->Path_Enemy.begin(); item != this->Path_Enemy.cend(); ++item) {
		if ((*item) == pos) {
			return true;
		}
	}
	return false;
}