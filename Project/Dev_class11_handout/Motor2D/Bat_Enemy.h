#ifndef _BAT_ENEMY_
#define _BAT_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"

class Bat_Enemy : public Enemy {
public:
	Bat_Enemy();
	Bat_Enemy(const Bat_Enemy&);
	~Bat_Enemy();
	void Action();
	//void Rang_Player();
public:
	iPoint temp_point = { 0,0 };

};


#endif