#ifndef _J1ACTIONS_
#define _J1ACTIONS_

#include "j1Module.h"
#include "Character.h"

class j1Actions : public j1Module {
public :
	j1Actions() {};
	~j1Actions() {};

public:
	void AddActionMove(Character*, direction, int distance);
	void AddActionAttack(Character*, direction, int times = 0);
	void AddActionWait(Character*, direction, int ms_time);
	void AddActionChangeDirection(Character*, direction);


};

#endif
