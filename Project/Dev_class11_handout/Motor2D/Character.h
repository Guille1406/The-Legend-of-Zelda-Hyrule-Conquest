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
#include "j1Object.h"


#define TILE_COL_ID 419

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


enum player_event {
	move,
	idle,
	jump,
	attack,
	roll,
	fall
	/*
	.
	.
	.
	*/
};

enum direction {
	up,
	down,
	left,
	right
};

enum move_direction {
	move_idle,
	move_up,
	move_down,
	move_right,
	move_left,
	move_up_left,
	move_up_right,
	move_down_left,
	move_down_right
};

class P_Link;
class P_Zelda;

enum movement_animation;
enum key_state;

class Character : public Entity {
public:
	Character() {};
	~Character() {};
	
	void Attack() {};
	void Move(float dt);
	void Jump(float dt);
	void Roll(float dt);
	virtual void LoadAnimation(const char*);
	virtual void ChangeAnimation(int);
	virtual player_event GetEvent();
	virtual void ExecuteEvent(float);
	void GetAdjacents();
	int GetLogic(bool collisions = false);
	uint GetLogicHeightPlayer();

private:
	void MoveFunction(float dt, int& pos,int& other_pos, bool add, dir_tiles tiles, int side_tile_one, int side_tile_two, bool is_down = false);
	void MoveDiagonalFunction(float dt, int& pos_one, int& pos_two, bool add_one, bool add_two, int front_tile, int side_tile, int diagonal_tile);
	void JumpFunction(float dt, int& pos, bool add);
	void RollFunction(float dt, int& pos, bool add);
	
public:
	
	SDL_Texture*	character_texture;
	iPoint	pos;
	iPoint	tilepos;
	adjacent_tiles	adjacent;
	

	p2SString					sprites_folder;
	pugi::xml_document			sprites_file;
	std::vector<Animation>*		sprites_vector;
	Animation					actual_animation; // pointer?

	player_event				actual_event;
	direction					character_direction;
	move_direction				movement_direction;

	bool doing_script = false;
	Collider* collision;
	int last_animation = 0;

	std::vector<bool> allow_collision;

private:
	uint i_logic_height_player = 0;

	//For jump
	int final_pos = 0;
	bool temp = false; //Needed to save position only one time
};

#endif

