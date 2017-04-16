#ifndef _CHAMPIONSOLDIER_ENEMY_
#define _CHAMPIONSOLDIER_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"
class Championsoldier_Enemy : public Enemy {
public:
	Championsoldier_Enemy();
	Championsoldier_Enemy(const Championsoldier_Enemy&);
	~Championsoldier_Enemy();
	void Action();
	void Rang_Player();

public:
	iPoint temp_point = { 0,0 };
};


#endif
