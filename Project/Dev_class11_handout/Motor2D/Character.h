#ifndef _CHARACTER_
#define _CHARACTER_

#include "j1Player.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class P_Link;
class P_Zelda;

class Character {
public:
	Character() {};
	~Character() {};
	
	void Attack() {};


public:

	SDL_Texture* character_texture;
	p2Point<int> pos;
	p2Point<int> tilepos;
};

#endif

