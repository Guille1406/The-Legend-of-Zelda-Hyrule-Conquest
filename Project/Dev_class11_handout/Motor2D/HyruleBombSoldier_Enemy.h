#ifndef _HYRULEBOMBSOLDIER_ENEMY_
#define _HYRULEBOMBSOLDIER_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"
class HyruleBombSoldier_Enemy : public Enemy {
public:
	HyruleBombSoldier_Enemy();
	HyruleBombSoldier_Enemy(const HyruleBombSoldier_Enemy&);
	~HyruleBombSoldier_Enemy();
	void Action();


public:
	iPoint temp_point = { 0,0 };
	iPoint bomb_point = {0,0};
	iPoint max_bomb_point = {0,0};
	iPoint player_position = { 0,0 };
	float t = 0;
	int off_set = 100;
	bool can_throw_bomb = true;
	bool continue_path_bomb = false;
	j1Timer bomb_timer;
};


#endif
