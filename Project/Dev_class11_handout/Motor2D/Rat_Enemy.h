#ifndef _RAT_ENEMY_
#define _RAT_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"

class Rat_Enemy : public Enemy {
public:
	Rat_Enemy();
	Rat_Enemy(const Rat_Enemy&);
	~Rat_Enemy();
	void Action();
	//void Rang_Player();
public:
	iPoint temp_point = { 0,0 };

};


#endif