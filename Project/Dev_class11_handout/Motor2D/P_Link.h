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
		
	}
	~P_Link() {
		delete sprites_vector;
	}

	void Attack();
	

	player_event GetEvent();

public:
	
};

#endif

