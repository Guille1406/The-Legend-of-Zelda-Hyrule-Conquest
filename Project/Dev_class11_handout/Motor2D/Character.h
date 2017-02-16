#ifndef _CHARACTER_
#define _CHARACTER_

#include "j1Player.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class Character {
public:
	Character() {};
	~Character() {};

	void Move() {
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			pos.y = pos.y - 1;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			pos.y = pos.y + 1;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			pos.x = pos.x - 1;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			pos.x = pos.x + 1;
		}
	};

	void Attack() {};


public:

	SDL_Texture* character_texture;
	p2Point<int> pos;

};

#endif

