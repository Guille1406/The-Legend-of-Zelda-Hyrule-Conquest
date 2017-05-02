#ifndef _SKULLROPE_ENEMY_
#define _SKULLROPE_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"

class SkullRope_Enemy : public Enemy {
public:
	SkullRope_Enemy();
	SkullRope_Enemy(const SkullRope_Enemy&);
	~SkullRope_Enemy();
	void Action();
	//void Rang_Player();
public:
	iPoint temp_point = { 0,0 };

};


#endif