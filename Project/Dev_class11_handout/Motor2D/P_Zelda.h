#ifndef _PZELDA_
#define _PZELDA_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"
#include "j1Collision.h"
#include "j1Enemy.h"

class Character;

enum arrow_direction {
	arrow_up,
	arrow_down,
	arrow_left,
	arrow_right
};

struct Arrow : public Entity{
	

	Arrow() {
		can_move = true;
		is_attached = false;
		entity_texture = App->object->objects_texture;
		Enemy* attached_enemy = nullptr;
		
	}
	iPoint pos = {0,0};
	int timer = 0;
	arrow_direction direction = arrow_up;
	bool can_move = false;
	bool is_attached = false;
	Enemy* attached_enemy = nullptr;
	iPoint offset = { 0,0 };
	int max_distance = 0;
	bool temp = false;
	int before_wall_pos = 0;
	SDL_Rect arrow_rect = rect_arrow_down;


	bool Check_Wall();
	bool Check_Wall_Loop( int &pos, bool add, bool is_horitzontal);
	int GetLogicArrow(int minus_height, iPoint pos);
};

class P_Zelda:public Character {
public:
	P_Zelda() {
		//sprites_vector = new std::vector<Animation>;
		//Vec_Arrow = new std::vector<Arrow*>;
		
	
	};
	~P_Zelda() {
		//delete sprites_vector;
	};

	void Attack(float dt);
	void ThrowFunction(float dt, int &pos, bool add, bool is_horitzontal);
	void CreateArrow(SDL_Rect);
	void UpdateArrows(int height);
	player_event GetEvent();

public:
	bool is_picked = false;
	bool temp = false;
	bool collide_jump = false;
	bool can_move =true;
	int bow = 0;
	uint Throw_Audio = 0;
	uint Arrow_Audio = 0;
	uint Arrow_Hit_Wall_Audio = 0;
	std::vector<Arrow*> Vec_Arrow;
	bool can_throw = false;
};

#endif

