#ifndef _PZELDA_
#define _PZELDA_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"

class Character;

class P_Zelda:public Character {
public:
	P_Zelda() {
		sprites_vector = new std::vector<Animation>;
	
	};
	~P_Zelda() {
		delete sprites_vector;
	};

	void Attack();
	

	player_event GetEvent();

public:

};

#endif

