#ifndef _PLINK_
#define _PLINK_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"
#include <vector>
class Character;

struct Sword : public Entity {

	iPoint pos;
	bool can_move;
	bool is_attached;
	Collider* Sword_Attack_Collider;
	Enemy* attached_enemy;
};

class P_Link:public Character  {
public:
	
	P_Link() {
		sprites_vector = new std::vector<Animation>;
		
	}
	~P_Link() {
		delete sprites_vector;
	}

	void Attack(float dt);
	j1Timer attack_timer;
	Sword* Link_sword;
	player_event GetEvent();

public:
	
	bool can_pick_up = false;
	bool im_lifting = false;

	bool temp = false;
};

#endif

