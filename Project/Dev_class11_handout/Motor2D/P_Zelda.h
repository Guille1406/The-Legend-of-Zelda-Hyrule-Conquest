#ifndef _PZELDA_
#define _PZELDA_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"
#include "j1Collision.h"
#include "j1Enemy.h"

class Character;

struct Arrow : public Entity{
	
	iPoint pos;
	int timer;
	int direction;
	bool can_move;
	bool is_attached;
	Enemy* attached_enemy;
	iPoint offset;

	bool Check_Wall();
	bool Check_Wall_Loop( int &pos, bool add, bool is_horitzontal);
	int GetLogicArrow(int minus_height, iPoint pos);
};

class P_Zelda:public Character {
public:
	P_Zelda() {
		sprites_vector = new std::vector<Animation>;
		Vec_Arrow = new std::vector<Arrow*>;
	
	};
	~P_Zelda() {
		delete sprites_vector;
	};

	void Attack(float dt);
	void ThrowFunction(float dt, int &pos, bool add, bool is_horitzontal);
	void CreateArrow(SDL_Rect);
	void UpdateArrows();
	player_event GetEvent();

public:
	bool is_picked = false;
	bool temp = false;
	bool collide_jump = false;
	bool can_move = true;
	std::vector<Arrow*>* Vec_Arrow;
};

#endif

