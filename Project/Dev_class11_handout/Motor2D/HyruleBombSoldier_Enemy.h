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
	int t = 0;
};


#endif
