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


struct dir_tiles {
	uint i;
	uint j;
};

struct  adjacent_tiles {
	dir_tiles up;
	dir_tiles down;
	dir_tiles left;
	dir_tiles right;

};

class P_Link;
class P_Zelda;

enum movement_animation;
enum key_state;

class Character {
public:
	Character() {};
	~Character() {};
	
	void Attack() {};
	void Move(float);
	virtual void LoadAnimation(const char*);
	virtual void ChangeAnimation(movement_animation);
	virtual key_state GetEvent();
	void GetAdjacents();

	

public:
	
	SDL_Texture*	character_texture;
	p2Point<int>	pos;
	p2Point<int>	tilepos;
	adjacent_tiles	adjacent;

	p2SString					sprites_folder;
	pugi::xml_document			sprites_file;
	std::vector<Animation>*		sprites_vector;
	Animation					actual_animation;
};

#endif

