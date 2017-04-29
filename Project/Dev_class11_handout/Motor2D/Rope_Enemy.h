#ifndef _ROPE_ENEMY_
#define _ROPE_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"

class Rope_Enemy : public Enemy {
public:
	Rope_Enemy();
	Rope_Enemy(const Rope_Enemy&);
	~Rope_Enemy();
	void Action();
	//void Rang_Player();
public:
	iPoint temp_point = { 0,0 };

};


#endif