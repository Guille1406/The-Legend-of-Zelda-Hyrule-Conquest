#ifndef _CHARACTER_
#define _CHARACTER_

#include "PugiXml/src/pugixml.hpp"
#include "p2Point.h"
#include "SDL\include\SDL.h"
#include  "p2SString.h"
#include "Animation.h"
#include "j1Textures.h"
#include <vector>
#include "p2Log.h"

class P_Link;
class P_Zelda;

enum movement_animation {
	animation_up,
	animation_down,
	animation_left,
	animation_right
};

class Character {
public:
	Character() {};
	~Character() {};
	
	void Attack() {};
	virtual void LoadAnimation(const char*);

public:
	
	SDL_Texture* character_texture;
	p2Point<int> pos;
	p2Point<int> tilepos;

	p2SString					sprites_folder;
	pugi::xml_document			sprites_file;
	std::vector<Animation>*	sprites_vector;
	Animation actual_animation;
};

#endif

