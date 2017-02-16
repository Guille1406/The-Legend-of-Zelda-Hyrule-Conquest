#ifndef _CHARACTER_
#define _CHARACTER_

#include "j1Player.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class Character {
public:
	Character() {};
	~Character() {};

	virtual void Move() {};
	virtual void Attack() {};


public:

	SDL_Texture* character_texture;
	p2Point<int> pos;

};

#endif

