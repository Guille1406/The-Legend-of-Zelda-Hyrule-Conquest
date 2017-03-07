#ifndef _PZELDA_
#define _PZELDA_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"

class Character;

class P_Zelda:public Character {
public:
	P_Zelda() {};
	~P_Zelda() {};


	void Attack();
	void LoadAnimation(const char*);
	void ChangeAnimation(movement_animation);
	key_state GetEvent();

public:

	


};

#endif

