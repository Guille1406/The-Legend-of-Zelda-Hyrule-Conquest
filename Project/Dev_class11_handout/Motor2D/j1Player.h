#ifndef _J1PLAYER_
#define _J1PLAYER_

#include "j1Module.h"
#include "p2Point.h"
#include "MainScene.h"
#include "P_Link.h"
#include "P_Zelda.h"

#include "j1Map.h"



class P_Link;
class P_Zelda;
class Character;

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


class j1Player :public j1Module {
public:
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void Draw();

	void Move();
	void Change_Player();
	void Chase();
	bool Move_Camera();

public:
	
	bool change = false;
	MainScene* actual_scene;

	
	Character* selected_character;
	Character* other_character;
	P_Link* Link;
	P_Zelda* Zelda;

	//Colisions
	MapLayer* Colision;
	adjacent_tiles adjacent;


	int live;
};



#endif
