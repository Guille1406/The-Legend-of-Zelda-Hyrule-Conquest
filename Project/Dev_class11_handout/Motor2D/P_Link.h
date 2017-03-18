#ifndef _PLINK_
#define _PLINK_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"
#include <vector>
class Character;

class P_Link:public Character  {
public:
	
	P_Link() {
		sprites_vector = new std::vector<Animation>;
		allow_collision.push_back(false);
		allow_collision.push_back(true);
		allow_collision.push_back(true);
	}
	~P_Link() {
		delete sprites_vector;
	}

	void Attack();
	void LoadAnimation(const char*);

	player_event GetEvent();

public:
	
};

#endif

