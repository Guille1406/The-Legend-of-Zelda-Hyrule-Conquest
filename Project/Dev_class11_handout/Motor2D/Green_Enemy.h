#ifndef _GREEN_ENEMY_
#define _GREEN_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"
class Green_Enemy : public Enemy {
public:
	Green_Enemy();
	Green_Enemy(const Green_Enemy&);
	~Green_Enemy();
	void Action();
	iPoint CalculatePath();
	bool FindInPath(iPoint);
public:
	std::list<iPoint> Path_Enemy;
};


#endif

