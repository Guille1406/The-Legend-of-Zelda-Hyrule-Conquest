#ifndef _PLINK_
#define _PLINK_

#include "j1Player.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class P_Link  {
public:
	P_Link() {};
	~P_Link() {};

	void Move();
	void Attack();


public:

	SDL_Texture* Link_Sprite;
	p2Point<int> pos;

};

#endif

